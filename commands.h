#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <QGraphicsItem>
#include "graphicsscene.h"
#include "qgraphicsitemfactory.h"

class Mediator;

class Command : public QObject
{
	Q_OBJECT
public:
	virtual ~Command(){}
	virtual void initialize(Mediator* mediator);
	virtual void execute(QGraphicsItem *item) = 0;
protected:
	Mediator* mediator = nullptr;
};

class CommandMove : public Command
{
	Q_OBJECT
public:
	virtual void execute(QGraphicsItem *) final;
};

class CommandGroup : public Command
{
	Q_OBJECT
public:
	virtual void initialize(Mediator *mediator) final;
	virtual void execute(QGraphicsItem *) final;
public slots:
	void click(const QString&uid);
};

class CommandRemove : public Command
{
	Q_OBJECT
public:
	virtual void execute(QGraphicsItem *item) final;
};

class CommandSelect : public Command
{
public:
	virtual void execute(QGraphicsItem *item) final;
};

class CommandBrush : public Command
{
	Q_OBJECT
public:
	CommandBrush(const QString& uid);
	virtual void initialize(Mediator *mediator) final;
	virtual void execute(QGraphicsItem* item) final;
public slots:
	void click(const QString&uid);
	void mousemoved(const QPointF& pos);
private:
	bool draw = false;
};

class CommandGraphicsItem : public Command
{
public:
	CommandGraphicsItem(const QString& uid);
	virtual void execute(QGraphicsItem* item) final;
private:
	QGraphicsItemFactory factory;
	QString uid;
};

#endif // ICOMMAND_HPP
