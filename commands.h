#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <QGraphicsItem>
#include "graphicsscene.h"

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

#endif // ICOMMAND_HPP
