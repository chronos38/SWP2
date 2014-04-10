#include "qgraphicsitemprototype.h"
#include <QPainter>

QGraphicsItemPrototype::QGraphicsItemPrototype(QPolygonF polygon, bool isEllipse, QGraphicsItem *parent) :
	QGraphicsItem(parent),
	m_polygon(polygon),
	m_isEllipse(isEllipse)
{

}

QRectF QGraphicsItemPrototype::boundingRect() const
{
	return m_polygon.boundingRect();
}

void QGraphicsItemPrototype::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if(m_isEllipse) {
		painter->drawEllipse(m_polygon.boundingRect());
	} else {
		painter->drawPolygon(m_polygon);
	}
}

QGraphicsItemPrototype *QGraphicsItemPrototype::clone()
{
	/*QObject verbietet echten copyconstructor*/
	return new QGraphicsItemPrototype(m_polygon);
}
