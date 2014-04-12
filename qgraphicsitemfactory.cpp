#include "qgraphicsitemfactory.h"
#include <QPolygonF>

QGraphicsItemFactory::QGraphicsItemFactory()
{
	QPolygonF circle(QRectF(0,0,40,40));
	m_circle = new QGraphicsItemPrototype(circle, true);

	QPolygonF ellipse(QRectF(0,0,40,60));
	m_ellipse = new QGraphicsItemPrototype(ellipse, true);

	QPolygonF rect(QRectF(0,0,40,60));
	m_rect = new QGraphicsItemPrototype(rect);

	QPolygonF square(QRectF(0,0,40,40));
	m_square = new QGraphicsItemPrototype(square);

	QPolygonF triangle;
	triangle << QPointF(20, 20) << QPointF(-20, 20) << QPointF(0, 20);
	m_triangle = new QGraphicsItemPrototype(triangle);

	m_composite = new QGraphicsItemComposite();
}

QGraphicsItemFactory::~QGraphicsItemFactory()
{
	delete m_circle;
	delete m_ellipse;
	delete m_rect;
	delete m_square;
	delete m_triangle;
}

QGraphicsItem *QGraphicsItemFactory::makeCircle() const
{
	return m_circle->clone();
}

QGraphicsItem *QGraphicsItemFactory::makeEllipse() const
{
	return m_ellipse->clone();
}

QGraphicsItem *QGraphicsItemFactory::makeRect() const
{
	return m_rect->clone();
}

QGraphicsItem *QGraphicsItemFactory::makeSquare() const
{
	return m_square->clone();
}

QGraphicsItem *QGraphicsItemFactory::makeTriangle() const
{
	return m_triangle->clone();
}

QGraphicsItem *QGraphicsItemFactory::makeComposite() const
{
	return m_composite->clone();
}
