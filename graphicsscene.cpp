#include "graphicsscene.h"
#include <QGraphicsSceneMouseEvent>

GraphicsScene::GraphicsScene(int width, int height, QObject *parent) :
	QGraphicsScene(parent)
{
	setSceneRect(0, 0, width, height);
}

QPointF GraphicsScene::getPos() const
{
	return position;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (pressed) {
		position = event->scenePos();
		emit mousemove(event->scenePos());
	}

	QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		position = event->scenePos();
		pressed = true;
		emit mousepressed();
	}

	QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (pressed && event->button() == Qt::LeftButton) {
		update();
		position = event->scenePos();
		pressed = false;
		emit clicked();
		emit mousereleased();
	} else if (event->button() == Qt::LeftButton) {
		emit mousereleased();
	}

	QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseDoubleClickEvent(event);
}
