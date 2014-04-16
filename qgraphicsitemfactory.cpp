#include "qgraphicsitemfactory.h"
#include <QPolygonF>
#include "qexception.h"

QGraphicsItemFactory::QGraphicsItemFactory()
{
	m_registry["Circle"] = new QGraphicsItemPrototype(QPolygonF(QRectF(0, 0, 40, 40)), true);
	m_registry["Ellipse"] = new QGraphicsItemPrototype(QPolygonF(QRectF(0, 0, 40, 60)), true);
	m_registry["Rectangle"] = new QGraphicsItemPrototype(QPolygonF(QRectF(0, 0, 40, 60)));
	m_registry["Square"] = new QGraphicsItemPrototype(QPolygonF(QRectF(0, 0, 40, 40)));
	m_registry["Triangle"] = new QGraphicsItemPrototype(QPolygonF(QVector<QPointF>({
								 QPointF(20, 20),
								 QPointF(-20, 20),
								 QPointF(0, 50)})));
}

QGraphicsItemFactory::~QGraphicsItemFactory()
{
	for (auto it : m_registry) {
		delete it;
	}
}

QGraphicsItem *QGraphicsItemFactory::create(const QString &uid)
{
	if (uid == "Composite") {
		return new QGraphicsItemComposite();
	} else if (uid == "Path") {
		return new QGraphicsPathItem();
	} else if (!m_registry.contains(uid)) {
		return nullptr;
	}

	return m_registry[uid]->clone();
}

QList<QString> QGraphicsItemFactory::getUids() const
{
	return m_registry.keys();
}
