#ifndef BUTTONWIDGETMEDIATOR_H
#define BUTTONWIDGETMEDIATOR_H

#include <QHash>
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
public:
	Mediator(QWidget* parent = 0);
	virtual ~Mediator(){}
	virtual GraphicsScene* getScene() const = 0;
	virtual QList<QGraphicsItem*> getSelected() const = 0;
	virtual void clearSelection() = 0;
};

class ButtonWidgetMediator : public Mediator
{
	Q_OBJECT
public:
	explicit ButtonWidgetMediator(QWidget *parent = 0);
	virtual ~ButtonWidgetMediator();

	virtual void registerButton(const QString& uid);
	virtual void registerScene(GraphicsScene* scene);
	virtual GraphicsScene *getScene() const final;
	virtual QList<QGraphicsItem*> getSelected() const final;
	virtual void clearSelection() final;

private slots:
	void sceneClicked();
	void buttonClicked();

protected:
	void addItem();
	void handleItem(QGraphicsItem* item);

private:
	QGraphicsItemFactory* factory = new QGraphicsItemFactory();
	QHash<QString, QPushButton*> registry;
	QHash<QString, Command*> commands;
	QList<QGraphicsItem*> selected;
	GraphicsScene* scene = nullptr;
	QVBoxLayout *layout = nullptr;
	QString uid;
};

#endif // BUTTONWIDETMEDIATOR_H
