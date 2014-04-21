#include "commands.h"
#include "qgraphicsitemcomposite.h"
#include "buttonwidgetmediator.h"

void Command::initialize(Mediator *mediator)
{
	this->mediator = mediator;
}

void CommandMove::execute(QGraphicsItem *)
{
}

void CommandGroup::initialize(Mediator *mediator)
{
	connect(mediator, SIGNAL(clicked(QString)), this, SLOT(click(QString)));
	Command::initialize(mediator);
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

void CommandBrush::initialize(Mediator *mediator)
{
	connect(mediator, SIGNAL(clicked(QString)), this, SLOT(click(QString)));
	connect(mediator, SIGNAL(mousemove(QPointF)), this, SLOT(mousemoved(QPointF)));
	Command::initialize(mediator);
}

void CommandBrush::execute(QGraphicsItem *item)
{
}

void CommandBrush::click(const QString &uid)
{
	draw = (uid == "Pen");
}

void CommandBrush::mousemoved(const QPointF &pos)
{
	if (!draw) {
		return;
	}
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
