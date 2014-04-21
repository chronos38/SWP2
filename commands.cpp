#include "commands.h"
#include "qgraphicsitemcomposite.h"
#include "buttonwidgetmediator.h"

void Command::initialize(Mediator *mediator)
{
	this->mediator = mediator;
	connect(mediator, SIGNAL(clicked(QString)), this, SLOT(click(QString)));
	connect(mediator, SIGNAL(mousemove(QPointF)), this, SLOT(mousemoved(QPointF)));
}

void Command::click(const QString &uid)
{
}

void Command::mousemoved(const QPointF &pos)
{
}

void CommandMove::execute(QGraphicsItem *)
{
}

void CommandGroup::execute(QGraphicsItem *)
{
}

void CommandGroup::click(const QString &uid)
{
	if (uid != "Group") {
		return;
	}

	QList<QGraphicsItem*> selected = mediator->getSelection();

	if (selected.empty()) {
		return;
	} else if (selected.length() == 1) {
		QGraphicsItemComposite* c = nullptr;

		if ((c = dynamic_cast<QGraphicsItemComposite*>(selected.first()))) {
			c->release();
		}

		return;
	}

	QGraphicsItemComposite* composite = new QGraphicsItemComposite();

	for (QGraphicsItem* item : selected) {
		QGraphicsItemComposite* c = nullptr;

		if ((c = dynamic_cast<QGraphicsItemComposite*>(item))) {
			auto children = c->release();

			for (QGraphicsItem* child : children) {
				composite->add(child);
			}
		} else {
			composite->add(item);
			mediator->getScene()->removeItem(item);
		}
	}

	composite->adjustPosition();
	mediator->getScene()->addItem(composite);
	mediator->clearSelection();

	Command::click(uid);
}

void CommandRemove::execute(QGraphicsItem *item)
{
	mediator->getScene()->removeItem(item);
}


void CommandSelect::execute(QGraphicsItem *item)
{
	if (!item) {
		return;
	}

	mediator->toggleSelection(item);
}


CommandBrush::CommandBrush(const QString &)
{
}

void CommandBrush::execute(QGraphicsItem *item)
{
}

void CommandBrush::click(const QString &uid)
{
	draw = (uid == "Brush");

	Command::click(uid);
}

void CommandBrush::mousemoved(const QPointF &pos)
{
	if (!draw) {
		return;
	}

	Command::mousemoved(pos);
}


CommandGraphicsItem::CommandGraphicsItem(const QString &uid)
{
	this->uid = uid;
}

void CommandGraphicsItem::execute(QGraphicsItem *i)
{
	if (i) {
		return;
	}

	GraphicsScene* scene = mediator->getScene();
	QGraphicsItem* item = factory.create(uid);
	QPointF pos = scene->getPos();
	QRectF rect;

	if (!item) {
		return;
	}

	rect = item->boundingRect();
	pos = QPointF(pos.x() - rect.width() / 2, pos.y() - rect.height() / 2);
	item->setPos(pos);
	scene->addItem(item);
}

void CommandResize::execute(QGraphicsItem *item)
{
}

void CommandResize::click(const QString &uid)
{
	QList<QGraphicsItem*> selection = mediator->getSelection();

	if (uid == "Enlarge") {
		for (QGraphicsItem* item : selection) {
			qreal scale = item->scale();

			if (scale <= 2.0) {
				item->setScale(scale * 1.1);
			}
		}
	} else if (uid == "Reduce") {
		for (QGraphicsItem* item : selection) {
			qreal scale = item->scale();

			if (scale >= 0.1) {
				item->setScale(scale / 1.1);
			}
		}
	}

	Command::click(uid);
}
