#include "buttonwidgetmediator.h"
#include <QDebug>
#include "qexception.h"
#include "graphicsscene.h"

ButtonWidgetMediator::ButtonWidgetMediator(QWidget *parent) :
	QWidget(parent),
	layout(new QVBoxLayout())
{
	this->setLayout(layout);
	this->show();
	QList<QString> uids = factory->getUids();

	registerButton("Move", new QPushButton("Move"));

	for (QString& uid : uids) {
		registerButton(uid, new QPushButton(uid));
	}

	registerScene(new GraphicsScene());
}

ButtonWidgetMediator::~ButtonWidgetMediator()
{
	if (scene) {
		delete scene;
	}

	delete factory;
}

void ButtonWidgetMediator::registerButton(const QString &uid, QPushButton *button)
{
	if (!button) {
		throw QArgumentNullException();
	} else if (registry.contains(uid)) {
		throw QException();
	}

	registry[uid] = button;
	layout->addWidget(button);
	connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void ButtonWidgetMediator::registerScene(GraphicsScene *scene)
{
	if (!scene) {
		throw QException();
	} else if (this->scene) {
		this->scene->deleteLater();
	}

	this->scene = scene;
	connect(this->scene, SIGNAL(clicked()), this, SLOT(addItem()));
}

GraphicsScene *ButtonWidgetMediator::getScene() const
{
	return scene;
}

void ButtonWidgetMediator::addItem()
{
	if (!scene) {
		throw QException();
	}

	QGraphicsItem* item = factory->create(uid);

	if (!item) {
		return;
	}

	item->setPos(scene->getPos());
	item->setFlag(QGraphicsItem::ItemIsMovable);
	scene->addItem(item);
}

void ButtonWidgetMediator::buttonClicked()
{
	if (!scene) {
		return;
	}

	QPushButton* button = qobject_cast<QPushButton*>(sender());
	this->uid = registry.key(button);
}
