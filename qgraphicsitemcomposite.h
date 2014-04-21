#ifndef GRAFICSITEMCOMPOSITE_HPP
#define GRAFICSITEMCOMPOSITE_HPP

#include <QList>
#include "qgraphicsitemprototype.h"

class QGraphicsItemComposite : public QGraphicsItem, public ColorSetter
{
public:
	typedef QList<QGraphicsItem*> Composite;
	typedef Composite::iterator Iterator;
	typedef Composite::const_iterator ConstIterator;

	QGraphicsItemComposite(QGraphicsItem *parent = 0);
	QGraphicsItemComposite(const QGraphicsItemComposite&) = delete;
	Composite release();
	void add(QGraphicsItem* component);
	void remove(QGraphicsItem* component);
	QGraphicsItem* getChild(int index);
	const QGraphicsItem* getChild(int index) const;
	bool contains(QGraphicsItem* item) const;
	void adjustPosition();

	virtual QRectF boundingRect() const final;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;

	virtual void setColor(QColor color) final;
protected:
	void computeSize(qreal &xmin, qreal &xmax, qreal &ymin, qreal &ymax) const;
private:
	Composite children;
	qreal x, y;
};

#endif // GRAFICSITEMCOMPOSITE_HPP
