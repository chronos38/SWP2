#include "buttonwidgetmediator.h"
#include <QDebug>
#include "qexception.h"
#include "graphicsscene.h"

Mediator::Mediator(QWidget *parent) :
	QWidget(parent)
{
}

ButtonWidgetMediator::ButtonWidgetMediator(QWidget *parent) :
	Mediator(parent),
	layout(new QVBoxLayout())
{
	this->setLayout(layout);
	this->show();
	QList<QString> uids = factory->getUids();

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

	for (Command* command : commands) {
		delete command;
	}

	factory->deleteLater();
}

void ButtonWidgetMediator::registerCommand(const QString &uid, Command *command)
{
	commands[uid] = command;
	command->initialize(this);
	registerButton(uid);
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

QList<QGraphicsItem *> ButtonWidgetMediator::getSelection() const
{
	return selected;
}

void ButtonWidgetMediator::toggleSelection(QGraphicsItem *item)
{
	if (selected.contains(item)) {
		selected.removeAll(item);
	} else {
		selected.append(item);
	}
}

void ButtonWidgetMediator::clearSelection()
{
	selected = QList<QGraphicsItem *>();
}

void ButtonWidgetMediator::sceneClicked()
{
	if (!scene) {
		return;
	}

	QGraphicsItem* item = scene->itemAt(scene->getPos(), QTransform());

	if (!item && factory->getUids().contains(uid)) {
		addItem();
	} else if (item) {
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
	emit clicked(uid);
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

	Command* command = commands[uid];

	if (command) {
		command->execute(item);
	}
}
