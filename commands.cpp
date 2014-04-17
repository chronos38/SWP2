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
	this->mediator = mediator;
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
	QList<QGraphicsItem*> selected = mediator->getSelected();

	if (selected.length() <= 1) {
		return;
	}

	for (QGraphicsItem* item : selected) {
		composite->add(item);
		mediator->getScene()->removeItem(item);
	}

	composite->adjustPosition();
	mediator->getScene()->addItem(composite);
	mediator->clearSelection();
}

void CommandRemove::execute(QGraphicsItem *item)
{
	mediator->getScene()->removeItem(item);
}
