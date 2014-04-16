#ifndef QGRAPHICSITEMFACTORY_H
#define QGRAPHICSITEMFACTORY_H

#include <QHash>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include "qgraphicsitemprototype.h"
#include "qgraphicsitemcomposite.h"

class QGraphicsItemFactory
{
public:
	QGraphicsItemFactory();
	~QGraphicsItemFactory();

	QGraphicsItem *create(const QString& uid);
	QList<QString> getUids() const;
private:
	QHash<QString, QGraphicsItemPrototype*> m_registry;
};

#endif // QGRAPHICSITEMFACTORY_H
