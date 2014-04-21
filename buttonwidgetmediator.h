#ifndef BUTTONWIDGETMEDIATOR_H
#define BUTTONWIDGETMEDIATOR_H

#include <QMap>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "qgraphicsitemfactory.h"
#include "qgraphicsitemcomposite.h"
#include "graphicsscene.h"
#include "commands.h"

class Mediator : public QWidget
{
	Q_OBJECT
signals:
	void clicked(const QString& uid);
	void mousemove(const QPointF & pos);
public:
	Mediator(QWidget* parent = 0);
	virtual ~Mediator(){}
	virtual void registerCommand(const QString& uid, Command* command) = 0;
	virtual void registerButton(const QString& uid) = 0;
	virtual void registerScene(GraphicsScene* scene) = 0;
	virtual GraphicsScene* getScene() const = 0;
	virtual QList<QGraphicsItem*> getSelection() const = 0;
	virtual void toggleSelection(QGraphicsItem* item) = 0;
	virtual void clearSelection() = 0;
};

class ButtonWidgetMediator : public Mediator
{
	Q_OBJECT
public:
	explicit ButtonWidgetMediator(QWidget *parent = 0);
	virtual ~ButtonWidgetMediator();

	virtual void registerCommand(const QString& uid, Command* command) final;
	virtual void registerButton(const QString& uid) final;
	virtual void registerScene(GraphicsScene* scene) final;
	virtual GraphicsScene *getScene() const final;
	virtual QList<QGraphicsItem*> getSelection() const final;
	virtual void toggleSelection(QGraphicsItem *item) final;
	virtual void clearSelection() final;

public slots:
	void mousemoved(const QPointF& pos);

private slots:
	void sceneClicked();
	void buttonClicked();

protected:
	void handleItem(QGraphicsItem* item);
	QGraphicsItem *getParent(QGraphicsItem *item);

private:
	QMap<QString, QPushButton*> registry;
	QMap<QString, Command*> commands;
	QList<QGraphicsItem*> selected;
	GraphicsScene* scene = nullptr;
	QVBoxLayout *layout = nullptr;
	QString uid;
};

#endif // BUTTONWIDETMEDIATOR_H
