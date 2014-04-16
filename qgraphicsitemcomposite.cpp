#include "qgraphicsitemcomposite.h"
#include "qexception.h"

QGraphicsItemComposite::QGraphicsItemComposite(QGraphicsItem *parent)
{
	setParentItem(parent);
}

void QGraphicsItemComposite::add(QGraphicsItem *component)
{
	// check argument
	if (!component) {
		throw QArgumentNullException();
	}

	component->setParentItem(this);
	m_children.push_back(component);
}

void QGraphicsItemComposite::remove(QGraphicsItem *component)
{
	// check argument
	if (!component) {
		throw QArgumentNullException();
	}

	// variables
	int index = m_children.indexOf(component);

	// remove
	if (index < 0) {
		return;
	}

	getChild(index)->setParentItem(0);
	m_children.removeAt(index);
}

QGraphicsItem* QGraphicsItemComposite::getChild(int index)
{
	// check argument
	if (index < 0) {
		throw QArgumentOutOfRangeException();
	} else if (index >= m_children.length()) {
		throw QArgumentOutOfRangeException();
	}

	return m_children.at(index);
}

const QGraphicsItem* QGraphicsItemComposite::getChild(int index) const
{
	// check argument
	if (index < 0) {
		throw QArgumentOutOfRangeException();
	} else if (index >= m_children.length()) {
		throw QArgumentOutOfRangeException();
	}

	return m_children.at(index);
}

QRectF QGraphicsItemComposite::boundingRect() const
{
	// variables
	QSizeF size(0, 0);

	for (auto child : m_children) {
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
	for (auto child : m_children) {
		child->paint(painter, option, widget);
	}
}
