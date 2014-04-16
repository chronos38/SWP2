#ifndef GRAFICSITEMCOMPOSITE_HPP
#define GRAFICSITEMCOMPOSITE_HPP

#include <QList>
#include "qgraphicsitemprototype.h"

class QGraphicsItemComposite : public QGraphicsItemPrototype
{
	QList<QGraphicsItemPrototype*> m_children;
	typedef QList<QGraphicsItemPrototype*> Composite;
	typedef Composite::iterator Iterator;
	typedef Composite::const_iterator ConstIterator;
public:
	QGraphicsItemComposite(QGraphicsItem *parent = 0);
	QGraphicsItemComposite(const QGraphicsItemComposite&) = delete;
	void add(QGraphicsItemPrototype* component);
	void remove(QGraphicsItemPrototype* component);
	QGraphicsItemPrototype* getChild(int index);
	const QGraphicsItemPrototype* getChild(int index) const;

	virtual QRectF boundingRect() const final;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
	virtual QGraphicsItemPrototype* clone() final;
	virtual QGraphicsItemPrototype *clone(QGraphicsItem *parent) final;
private:
	explicit QGraphicsItemComposite(const Composite&);
	explicit QGraphicsItemComposite(const Composite&, QGraphicsItem *parent);
};

#endif // GRAFICSITEMCOMPOSITE_HPP
