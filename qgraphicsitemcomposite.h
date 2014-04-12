#ifndef GRAFICSITEMCOMPOSITE_HPP
#define GRAFICSITEMCOMPOSITE_HPP

#include <QVector>
#include "qgraphicsitemprototype.h"

class QGraphicsItemComposite : public QGraphicsItemPrototype
{
	QVector<QGraphicsItemPrototype*> m_children;
	typedef QVector<QGraphicsItemPrototype*> Composite;
	typedef Composite::iterator Iterator;
	typedef Composite::const_iterator ConstIterator;
public:
	QGraphicsItemComposite() = default;
	QGraphicsItemComposite(const QGraphicsItemComposite&) = delete;
	void add(QGraphicsItemPrototype* component);
	void remove(QGraphicsItemPrototype* component);
	QGraphicsItemPrototype* getChild(int index);
	const QGraphicsItemPrototype* getChild(int index) const;

	virtual QRectF boundingRect() const final;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
	virtual QGraphicsItemPrototype* clone() final;
private:
	explicit QGraphicsItemComposite(const QVector<QGraphicsItemPrototype*>&);
};

#endif // GRAFICSITEMCOMPOSITE_HPP
