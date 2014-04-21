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

	registerScene(new GraphicsScene(width(), height()));
}

ButtonWidgetMediator::~ButtonWidgetMediator()
{
	if (scene) {
		scene->deleteLater();
	}

	for (Command* command : commands) {
		delete command;
	}
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
	//connect(this->scene, SIGNAL(mousepressed()), this, SLOT(mousepressed()));
	//connect(this->scene, SIGNAL(mousereleased()), this, SLOT(mousereleased()));
	//connect(this->scene, SIGNAL(mousemove(QPointF)), this, SLOT(mousemoved(QPointF)));
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
		dynamic_cast<ColorSetter*>(item)->setColor(Qt::black);
		selected.removeAll(item);
	} else {
		dynamic_cast<ColorSetter*>(item)->setColor(Qt::red);
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

	handleItem(getParent(scene->itemAt(scene->getPos(), QTransform())));
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

void ButtonWidgetMediator::handleItem(QGraphicsItem *item)
{
	if (!scene) {
		return;
	}

	Command* command = commands[uid];

	if (command) {
		command->execute(item);
	}
}

QGraphicsItem *ButtonWidgetMediator::getParent(QGraphicsItem *item)
{
	if (!item) {
		return nullptr;
	}

	QGraphicsItem* result = item->parentItem();
	return (result ? getParent(result) : item);
}
