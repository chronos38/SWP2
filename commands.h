#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <QGraphicsItem>

class ICommand
{
public:
	virtual void execute(QGraphicsItem* item) = 0;
};

class CommandGroup : public ICommand
{
public:
	virtual void execute(QGraphicsItem *item);
};

class CommandRemove : public ICommand
{
public:
	virtual void execute(QGraphicsItem *item);
};

#endif // ICOMMAND_HPP
