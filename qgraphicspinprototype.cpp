#include "qgraphicspinprototype.h"
#include <QPainter>


QGraphicsPin::QGraphicsPin(QGraphicsItem *parent) :
	QGraphicsPathItem(parent)
{
}

QGraphicsPin::QGraphicsPin(const QPainterPath &path, QGraphicsItem *parent) :
	QGraphicsPathItem(path, parent)
{
}

void QGraphicsPin::setColor(QColor color)
{
	this->color = color;
}


QGraphicsAirBrush::QGraphicsAirBrush(QGraphicsItem *parent) :
	QGraphicsItem(parent)
{
}

QRectF QGraphicsAirBrush::boundingRect() const
{
	return QRectF();
}

void QGraphicsAirBrush::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setBrush(QBrush(color, Qt::Dense6Pattern));

	for (QPointF& point : points) {
		painter->drawEllipse(QRectF(point, QSizeF(8, 8)));
	}
}

void QGraphicsAirBrush::setColor(QColor color)
{
	this->color = color;
}

void QGraphicsAirBrush::add(const QPointF &point)
{
	points.append(point);
}
