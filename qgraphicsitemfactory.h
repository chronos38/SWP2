#ifndef QGRAPHICSITEMFACTORY_H
#define QGRAPHICSITEMFACTORY_H

#include <QMap>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include "qgraphicsitemprototype.h"

class QGraphicsItemFactory : public QObject
{
public:
	QGraphicsItemFactory();
	~QGraphicsItemFactory();

	QGraphicsItem *create(const QString& uid);
	QList<QString> getUids() const;
private:
	QMap<QString, QGraphicsItemPrototype*> registry;
};

#endif // QGRAPHICSITEMFACTORY_H
