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
	Command::initialize(mediator);
	connect(mediator, SIGNAL(clicked(QString)), this, SLOT(click(QString)));
}

void CommandGroup::execute(QGraphicsItem *)
{
}

void CommandGroup::click(const QString &uid)
{
	if (uid != "Group") {
		return;
	}

	QGraphicsItemComposite* composite = new QGraphicsItemComposite();
	QList<QGraphicsItem*> selected = mediator->getSelection();

	if (selected.length() <= 1) {
		QGraphicsItemComposite* c = nullptr;

		if ((c = dynamic_cast<QGraphicsItemComposite*>(selected.first()))) {
			c->release();
		}

		return;
	}

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
