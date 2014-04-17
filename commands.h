#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <QGraphicsItem>
#include "graphicsscene.h"

class ICommand
{
public:
	virtual QGraphicsItem* execute(GraphicsScene* scene, QGraphicsItem* item) = 0;
};

class CommandGroup : public ICommand
{
public:
	virtual QGraphicsItem* execute(GraphicsScene* scene, QGraphicsItem *item);
};

class CommandRemove : public ICommand
{
public:
	virtual QGraphicsItem* execute(GraphicsScene* scene, QGraphicsItem *item);
};

#endif // ICOMMAND_HPP
