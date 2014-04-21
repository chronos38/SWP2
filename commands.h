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
public slots:
	virtual void click(const QString&uid);
	virtual void mousemoved(const QPointF& pos);
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
	virtual void execute(QGraphicsItem *) final;
public slots:
	virtual void click(const QString&uid) final;
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
	virtual void execute(QGraphicsItem* item) final;
public slots:
	virtual void click(const QString&uid) final;
	virtual void mousemoved(const QPointF& pos) final;
private:
	bool draw = false;
};

class CommandGraphicsItem : public Command
{
	Q_OBJECT
public:
	CommandGraphicsItem(const QString& uid);
	virtual void execute(QGraphicsItem* item) final;
private:
	QGraphicsItemFactory factory;
	QString uid;
};

class CommandResize : public Command
{
	Q_OBJECT
public:
	virtual void execute(QGraphicsItem* item) final;
public slots:
	virtual void click(const QString&uid) final;
};

#endif // ICOMMAND_HPP
