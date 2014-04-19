#ifndef QGRAPHICSITEMPROTOTYPE_H
#define QGRAPHICSITEMPROTOTYPE_H

#include <QGraphicsItem>
#include <QPolygonF>
#include <QPen>

class ColorSetter
{
public:
	virtual void setColor(QColor color) = 0;
protected:
};

class QGraphicsItemPrototype : public QGraphicsItem, public ColorSetter
{
public:
	QGraphicsItemPrototype() = delete;
	QGraphicsItemPrototype(const QGraphicsItemPrototype&) = delete;
	explicit QGraphicsItemPrototype(QPolygonF polygon, bool isEllipse = false, QGraphicsItem *parent = 0);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
	virtual QGraphicsItemPrototype *clone();
	virtual void setColor(QColor color) final;
private:
	QPolygonF m_polygon;
	bool m_isEllipse;
	QPen pen = QPen(Qt::black);
};

#endif // QGRAPHICSITEMPROTOTYPE_H
