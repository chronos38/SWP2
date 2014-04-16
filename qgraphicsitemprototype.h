#ifndef QGRAPHICSITEMPROTOTYPE_H
#define QGRAPHICSITEMPROTOTYPE_H

#include <QGraphicsItem>
#include <QPolygonF>

class QGraphicsItemPrototype : public QGraphicsItem
{
public:
	QGraphicsItemPrototype() = delete;
	QGraphicsItemPrototype(const QGraphicsItemPrototype&) = delete;
	explicit QGraphicsItemPrototype(QPolygonF polygon, bool isEllipse = false, QGraphicsItem *parent = 0);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
	virtual QGraphicsItemPrototype *clone();
private:
	QPolygonF m_polygon;
	bool m_isEllipse;
};

#endif // QGRAPHICSITEMPROTOTYPE_H
