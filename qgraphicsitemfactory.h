#ifndef QGRAPHICSITEMFACTORY_H
#define QGRAPHICSITEMFACTORY_H

#include <QGraphicsItem>
#include "qgraphicsitemprototype.h"
#include "qgraphicsitemcomposite.h"

class QGraphicsItemFactory
{
public:
	QGraphicsItemFactory();
	~QGraphicsItemFactory();

	QGraphicsItem *makeCircle() const;
	QGraphicsItem *makeEllipse() const;
	QGraphicsItem *makeRect() const;
	QGraphicsItem *makeSquare() const;
	QGraphicsItem *makeTriangle() const;
	QGraphicsItem *makeComposite() const;
private:
	QGraphicsItemPrototype * m_circle;
	QGraphicsItemPrototype * m_ellipse;
	QGraphicsItemPrototype * m_rect;
	QGraphicsItemPrototype * m_square;
	QGraphicsItemPrototype * m_triangle;
	QGraphicsItemComposite * m_composite;
};

#endif // QGRAPHICSITEMFACTORY_H
