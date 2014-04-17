#include "qgraphicsitemcomposite.h"
#include "qexception.h"
#include <cmath>

QGraphicsItemComposite::QGraphicsItemComposite(QGraphicsItem *parent) :
	QGraphicsItem(parent)
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
}

void QGraphicsItemComposite::add(QGraphicsItem *component)
{
	// check argument
	if (!component) {
		throw QArgumentNullException();
	}

	component->setParentItem(this);
	component->setFlag(QGraphicsItem::ItemIsMovable, false);
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
	component->setFlag(QGraphicsItem::ItemIsMovable, true);
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

void QGraphicsItemComposite::adjustPosition()
{
	qreal xmin, xmax, ymin, ymax;

	computeSize(xmin, xmax, ymin, ymax);
	setPos(xmin, ymin);

	for (QGraphicsItem* child : children) {
		child->setX(std::abs(xmin) + child->x());
		child->setY(std::abs(ymin) + child->y());
	}
}

QRectF QGraphicsItemComposite::boundingRect() const
{
	// variables
	qreal xmin, xmax, ymin, ymax;
	computeSize(xmin, xmax, ymin, ymax);
	return QRectF(QPointF(), QRectF(QPointF(xmin, ymin), QPointF(xmax, ymax)).size());
}

void QGraphicsItemComposite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	/*for (auto child : children) {
		child->paint(painter, option, widget);
	}*/
}

void QGraphicsItemComposite::computeSize(qreal &xmin, qreal &xmax, qreal &ymin, qreal &ymax) const
{
	if (children.empty()) {
		xmin = xmax = ymin = ymax = 0;
		return;
	}

	xmin = xmax = children.first()->x();
	ymin = ymax = children.first()->y();

	for (int i = 1; i < children.length(); i++) {
		QGraphicsItem* child = children.at(i);

		if (xmin > child->x()) {
			xmin = child->x();
		}

		if (xmax < child->x()) {
			xmax = child->x();
		}

		if (ymin > child->y()) {
			ymin = child->y();
		}

		if (ymax < child->y()) {
			ymax = child->y();
		}
	}
}
