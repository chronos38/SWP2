#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit GraphicsScene(int width, int height, QObject *parent = 0);
	QPointF getPos() const;

signals:
	void clicked();
	void mousepressed();
	void mousereleased();
	void mousemove(const QPointF & pos);

public slots:

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
	bool pressed = false;
	QPointF position;
};

#endif // GRAPHICSSCENE_H
