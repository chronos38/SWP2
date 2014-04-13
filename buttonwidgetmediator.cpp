#include "buttonwidgetmediator.h"
#include <QDebug>

ButtonWidgetMediator::ButtonWidgetMediator(QWidget *parent) :
	QWidget(parent),
	layout(new QVBoxLayout()),
	handButton(new QPushButton("Verschieben", this)),
	penButton1(new QPushButton("Pinsel1", this)),
	penButton2(new QPushButton("Pinsel2", this)),
	rectButton(new QPushButton("Rechteck", this)),
	squareButton(new QPushButton("Quadrat", this)),
	circleButton(new QPushButton("Kreis", this)),
	ellipseButton(new QPushButton("Ellipse", this)),
	triangleButton(new QPushButton("Dreieck", this))
{
	layout->addWidget(handButton);
	layout->addWidget(penButton1);
	layout->addWidget(penButton2);
	layout->addWidget(rectButton);
	layout->addWidget(squareButton);
	layout->addWidget(circleButton);
	layout->addWidget(ellipseButton);
	layout->addWidget(triangleButton);

	connect(penButton1, SIGNAL(clicked()),this, SLOT(penButton1Pressed()));

	this->setLayout(layout);
	this->show();
}

ButtonWidgetMediator::~ButtonWidgetMediator()
{
	delete layout;
	delete penButton1;
	delete penButton2;
	delete rectButton;
	delete squareButton;
	delete circleButton;
	delete ellipseButton;
	delete triangleButton;
}

void ButtonWidgetMediator::penButton1Pressed()
{
	qDebug("blub");
}

void ButtonWidgetMediator::penButton2Pressed()
{

}


