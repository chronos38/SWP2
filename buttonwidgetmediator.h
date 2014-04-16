#ifndef BUTTONWIDGETMEDIATOR_H
#define BUTTONWIDGETMEDIATOR_H

#include <QHash>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "qgraphicsitemfactory.h"
#include "graphicsscene.h"

class ButtonWidgetMediator : public QWidget
{
	Q_OBJECT
public:
	explicit ButtonWidgetMediator(QWidget *parent = 0);
	~ButtonWidgetMediator();

	virtual void registerButton(const QString& uid, QPushButton* button);
	virtual void registerScene(GraphicsScene* scene);
	virtual GraphicsScene *getScene() const;
signals:
	void clicked(const QString& uid);

public slots:
	void addItem();

private slots:
	void buttonClicked();

private:
	QGraphicsItemFactory* factory = new QGraphicsItemFactory();
	QHash<QString, QPushButton*> registry;
	GraphicsScene* scene = nullptr;
	QVBoxLayout *layout = nullptr;
	QString uid;
};

#endif // BUTTONWIDETMEDIATOR_H
