#include "qgraphicsitemcomposite.h"
#include "qexception.h"
#include <cmath>

QGraphicsItemComposite::QGraphicsItemComposite(QGraphicsItem *parent) :
	QGraphicsItem(parent)
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
}

QGraphicsItemComposite::Composite QGraphicsItemComposite::release()
{
	Composite result = children;

	for (QGraphicsItem* child : children) {
		child->setParentItem(0);
	}

	children.clear();
	return result;
}

void QGraphicsItemComposite::add(QGraphicsItem *component)
{
	// check argument
	if (!component) {
		throw QArgumentNullException();
	}

	if (component->parentItem()) {
		dynamic_cast<QGraphicsItemComposite*>(component->parentItem())->remove(component);
	}

	dynamic_cast<ColorSetter*>(component)->setColor(Qt::green);
	component->setParentItem(this);
	component->setFlag(QGraphicsItem::ItemIsMovable, false);
	children.append(component);
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

	dynamic_cast<ColorSetter*>(children.at(index))->setColor(Qt::black);
	children.at(index)->setParentItem(0);
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
}

void QGraphicsItemComposite::setColor(QColor color)
{
	if (color == Qt::black) {
		for (QGraphicsItem* child : children) {
			dynamic_cast<ColorSetter*>(child)->setColor(Qt::green);
		}
	} else {
		for (QGraphicsItem* child : children) {
			dynamic_cast<ColorSetter*>(child)->setColor(color);
		}
	}
}

void QGraphicsItemComposite::computeSize(qreal &xmin, qreal &xmax, qreal &ymin, qreal &ymax) const
{
	if (children.empty()) {
		xmin = xmax = ymin = ymax = 0;
		return;
	}

	xmin = xmax = children.first()->x();
	ymin = ymax = children.first()->y();
	xmax += children.first()->boundingRect().width();
	ymax += children.first()->boundingRect().height();

	for (int i = 1; i < children.length(); i++) {
		QGraphicsItem* child = children.at(i);

		if (xmin > child->x()) {
			xmin = child->x();
		}

		if (xmax < child->x() + child->boundingRect().width()) {
			xmax = child->x() + child->boundingRect().width();
		}

		if (ymin > child->y()) {
			ymin = child->y();
		}

		if (ymax < child->y() + child->boundingRect().height()) {
			ymax = child->y() + child->boundingRect().height();
		}
	}
}
