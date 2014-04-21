#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <QGraphicsItem>
#include "graphicsscene.h"
#include "qgraphicsitemfactory.h"
#include "qgraphicspinprototype.h"

class Mediator;

class Command : public QObject
{
	Q_OBJECT
public:
	virtual ~Command(){}
	virtual void initialize(Mediator* mediator);
	virtual void execute(QGraphicsItem *item);
public slots:
	virtual void click(const QString&uid);
	virtual void mousepressed();
	virtual void mousereleased();
	virtual void mousemoved(const QPointF& pos);
protected:
	Mediator* mediator = nullptr;
};

class CommandMove : public Command
{
	Q_OBJECT
public:
};

class CommandGroup : public Command
{
	Q_OBJECT
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

class CommandEnlarge : public Command
{
	Q_OBJECT
public:
	virtual void execute(QGraphicsItem* item) final;
public slots:
	virtual void click(const QString&uid) final;
private:
	QString uid;
};

class CommandReduce : public Command
{
	Q_OBJECT
public:
	virtual void execute(QGraphicsItem* item) final;
public slots:
	virtual void click(const QString&uid) final;
private:
	QString uid;
};

class CommandPin1 : public Command
{
	Q_OBJECT
public:
	virtual void execute(QGraphicsItem* item) final;
public slots:
	virtual void click(const QString&uid) final;
	virtual void mousepressed() final;
	virtual void mousereleased() final;
	virtual void mousemoved(const QPointF& pos) final;
private:
	QString uid;
	bool draw = false;
	QGraphicsPin* item = nullptr;
	QPointF point;
};

class CommandPin2 : public Command
{
	Q_OBJECT
public:
	virtual void execute(QGraphicsItem* item) final;
public slots:
	virtual void click(const QString&uid) final;
	virtual void mousepressed() final;
	virtual void mousereleased() final;
	virtual void mousemoved(const QPointF& pos) final;
private:
	QString uid;
	bool draw = false;
	QGraphicsAirBrush* item = nullptr;
	QPointF point;
};

#endif // ICOMMAND_HPP
