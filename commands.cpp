#include "commands.h"
#include "qgraphicsitemcomposite.h"

QGraphicsItem* CommandGroup::execute(GraphicsScene* scene, QGraphicsItem *item)
{
	QGraphicsItemComposite* composite = dynamic_cast<QGraphicsItemComposite*>(item);

	if (composite) {
		if (composite->contains(item)) {
			composite->remove(item);
		} else {
			composite->add(item);
		}
	} else {
		composite = new QGraphicsItemComposite(item->parentItem());
		composite->add(item);
		return composite;
	}

	return nullptr;
}

QGraphicsItem* CommandRemove::execute(GraphicsScene* scene, QGraphicsItem *item)
{
	scene->removeItem(item);
	return nullptr;
}
