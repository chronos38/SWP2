#ifndef QGRAPHICSPINPROTOTYPE_HPP
#define QGRAPHICSPINPROTOTYPE_HPP

#include <QGraphicsPathItem>
#include "qgraphicsitemprototype.h"

class QGraphicsPin : public QGraphicsPathItem, public ColorSetter
{
public:
	QGraphicsPin(QGraphicsItem * parent = 0);
	QGraphicsPin(const QPainterPath & path, QGraphicsItem * parent = 0);

	virtual void setColor(QColor) final;

private:
	QColor color;
};

class QGraphicsAirBrush : public QGraphicsItem, public ColorSetter
{
public:
	QGraphicsAirBrush(QGraphicsItem* parent = 0);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	virtual void setColor(QColor) final;

	void add(const QPointF& point);
private:
	QColor color;
	QList<QPointF> points;
};

#endif // QGRAPHICSPINPROTOTYPE_HPP
