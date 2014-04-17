#ifndef GRAFICSITEMCOMPOSITE_HPP
#define GRAFICSITEMCOMPOSITE_HPP

#include <QList>
#include "qgraphicsitemprototype.h"

class QGraphicsItemComposite : public QGraphicsItem
{
	typedef QList<QGraphicsItem*> Composite;
	typedef Composite::iterator Iterator;
	typedef Composite::const_iterator ConstIterator;
public:
	QGraphicsItemComposite(QGraphicsItem *parent = 0);
	QGraphicsItemComposite(const QGraphicsItemComposite&) = delete;
	void add(QGraphicsItem* component);
	void remove(QGraphicsItem* component);
	QGraphicsItem* getChild(int index);
	const QGraphicsItem* getChild(int index) const;
	bool contains(QGraphicsItem* item) const;

	virtual QRectF boundingRect() const final;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
private:
	Composite children;
};

#endif // GRAFICSITEMCOMPOSITE_HPP
