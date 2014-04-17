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

	commands["Move"] = nullptr;
	commands["Remove"] = new CommandRemove();
	commands["Group"] = new CommandGroup();

	QList<QString> commandKeys = commands.keys();

	for (QString& uid : commandKeys) {
		registerButton(uid);
	}

	for (QString& uid : uids) {
		registerButton(uid);
	}

	registerScene(new GraphicsScene());
}

ButtonWidgetMediator::~ButtonWidgetMediator()
{
	if (scene) {
		scene->deleteLater();
	}

	factory->deleteLater();
}

void ButtonWidgetMediator::registerButton(const QString &uid)
{
	QPushButton* button = new QPushButton(uid);

	if (registry.contains(uid)) {
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
	connect(this->scene, SIGNAL(clicked()), this, SLOT(sceneClicked()));
}

GraphicsScene *ButtonWidgetMediator::getScene() const
{
	return scene;
}

void ButtonWidgetMediator::sceneClicked()
{
	if (!scene) {
		return;
	} else if (factory->getUids().contains(uid)) {
		addItem();
	} else {
		handleItem(scene->itemAt(scene->getPos(), QTransform()));
	}
}

void ButtonWidgetMediator::buttonClicked()
{
	if (!scene) {
		return;
	}

	QPushButton* button = qobject_cast<QPushButton*>(sender());
	this->uid = registry.key(button);
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
	scene->addItem(item);
}

void ButtonWidgetMediator::handleItem(QGraphicsItem *item)
{
	if (!scene) {
		return;
	} else if (!item) {
		return;
	}

	ICommand* command = commands[uid];

	if (command) {
		QGraphicsItem* result = command->execute(scene, item);

		if (result) {
			scene->addItem(result);
		}
	}
}
