#include "qgraphicsitemcomposite.h"
#include "qexception.h"

void QGraphicsItemComposite::add(QGraphicsItemPrototype *component)
{
	// check argument
	if (!component) {
		throw QArgumentNullException();
	}

	m_children.push_back(component);
}

void QGraphicsItemComposite::remove(QGraphicsItemPrototype *component)
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

	m_children.removeAt(index);
}

QGraphicsItemPrototype* QGraphicsItemComposite::getChilde(int index)
{
	// check argument
	if (index < 0) {
		throw QArgumentOutOfRangeException();
	} else if (index >= m_children.length()) {
		throw QArgumentOutOfRangeException();
	}

	return m_children.at(index);
}

const QGraphicsItemPrototype* QGraphicsItemComposite::getChilde(int index) const
{
	// check argument
	if (index < 0) {
		throw QArgumentOutOfRangeException();
	} else if (index >= m_children.length()) {
		throw QArgumentOutOfRangeException();
	}

	return m_children.at(index);
}

void QGraphicsItemComposite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	for (QGraphicsItemPrototype* child : m_children) {
		child->paint(painter, option, widget);
	}
}
