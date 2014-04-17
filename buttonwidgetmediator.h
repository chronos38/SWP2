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

class ButtonWidgetMediator : public QWidget
{
	Q_OBJECT
public:
	explicit ButtonWidgetMediator(QWidget *parent = 0);
	~ButtonWidgetMediator();

	virtual void registerButton(const QString& uid);
	virtual void registerScene(GraphicsScene* scene);
	virtual GraphicsScene *getScene() const;
signals:
	void clicked(const QString& uid);

private slots:
	void sceneClicked();
	void buttonClicked();

protected:
	void addItem();
	void handleItem(QGraphicsItem* item);

private:
	QGraphicsItemFactory* factory = new QGraphicsItemFactory();
	QHash<QString, QPushButton*> registry;
	QHash<QString, ICommand*> commands;
	GraphicsScene* scene = nullptr;
	QVBoxLayout *layout = nullptr;
	QString uid;
};

#endif // BUTTONWIDETMEDIATOR_H
