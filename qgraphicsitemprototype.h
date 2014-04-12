#ifndef QGRAPHICSITEMPROTOTYPE_H
#define QGRAPHICSITEMPROTOTYPE_H

#include <QGraphicsItem>
#include <QPolygonF>

class QGraphicsItemPrototype : public QGraphicsItem
{
public:
	QGraphicsItemPrototype(const QGraphicsItemPrototype&) = delete;
	explicit QGraphicsItemPrototype(QPolygonF polygon = QRectF(0,0,40,60), bool isEllipse = false, QGraphicsItem *parent = 0);

	QGraphicsItem *getParent() const;
	void setParent(QGraphicsItem *parent);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual QGraphicsItemPrototype *clone();
	virtual QGraphicsItemPrototype *clone(QGraphicsItem *parent);
private:
	QPolygonF m_polygon;
	bool m_isEllipse;
	QGraphicsItem* m_parent;
};

#endif // QGRAPHICSITEMPROTOTYPE_H
