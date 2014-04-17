#include "qgraphicsitemcomposite.h"
#include "qexception.h"

QGraphicsItemComposite::QGraphicsItemComposite(QGraphicsItem *parent)
{
	setParentItem(parent);
	setFlag(QGraphicsItem::ItemIsMovable);
}

void QGraphicsItemComposite::add(QGraphicsItem *component)
{
	// check argument
	if (!component) {
		throw QArgumentNullException();
	}

	this->setPos(component->x(), component->y());
	component->setParentItem(this);
	component->setPos(0, 0);
	children.push_back(component);
}

void QGraphicsItemComposite::remove(QGraphicsItem *component)
{
	// check argument
	if (!component) {
		throw QArgumentNullException();
	}

	// variables
	int index = children.indexOf(component);

	// remove
	if (index < 0) {
		return;
	}

	getChild(index)->setParentItem(parentItem());
	children.removeAt(index);
}

QGraphicsItem* QGraphicsItemComposite::getChild(int index)
{
	// check argument
	if (index < 0) {
		throw QArgumentOutOfRangeException();
	} else if (index >= children.length()) {
		throw QArgumentOutOfRangeException();
	}

	return children.at(index);
}

const QGraphicsItem* QGraphicsItemComposite::getChild(int index) const
{
	// check argument
	if (index < 0) {
		throw QArgumentOutOfRangeException();
	} else if (index >= children.length()) {
		throw QArgumentOutOfRangeException();
	}

	return children.at(index);
}

bool QGraphicsItemComposite::contains(QGraphicsItem *item) const
{
	return children.contains(item);
}

QRectF QGraphicsItemComposite::boundingRect() const
{
	// variables
	QSizeF size(0, 0);

	for (auto child : children) {
		QSizeF rectSize = child->boundingRect().size();

		if (rectSize.width() > size.width()) {
			size.setWidth(rectSize.width());
		}

		if (rectSize.height() > size.height()) {
			size.setHeight(rectSize.height());
		}
	}

	return QRectF(QPointF(), size);
}

void QGraphicsItemComposite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	for (auto child : children) {
		child->paint(painter, option, widget);
	}
}
