#include "commands.h"

void CommandGroup::execute(QGraphicsItem *item)
{

}

void CommandRemove::execute(QGraphicsItem *item)
{
	delete item;
}
