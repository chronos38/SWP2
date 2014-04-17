#include "qgraphicsitemfactory.h"
#include <QPolygonF>
#include "qexception.h"

QGraphicsItemFactory::QGraphicsItemFactory()
{
	registry["Circle"] = new QGraphicsItemPrototype(QPolygonF(QRectF(0, 0, 40, 40)), true);
	registry["Ellipse"] = new QGraphicsItemPrototype(QPolygonF(QRectF(0, 0, 40, 60)), true);
	registry["Rectangle"] = new QGraphicsItemPrototype(QPolygonF(QRectF(0, 0, 40, 60)));
	registry["Square"] = new QGraphicsItemPrototype(QPolygonF(QRectF(0, 0, 40, 40)));
	registry["Triangle"] = new QGraphicsItemPrototype(QPolygonF(QVector<QPointF>({
								 QPointF(20, 20),
								 QPointF(-20, 20),
								 QPointF(0, 50)})));
}

QGraphicsItemFactory::~QGraphicsItemFactory()
{
	for (auto it : registry) {
		delete it;
	}
}

QGraphicsItem *QGraphicsItemFactory::create(const QString &uid)
{
	if (!registry.contains(uid)) {
		return nullptr;
	}

	return registry[uid]->clone();
}

QList<QString> QGraphicsItemFactory::getUids() const
{
	return registry.keys();
}
