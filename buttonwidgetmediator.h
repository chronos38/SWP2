#ifndef BUTTONWIDGETMEDIATOR_H
#define BUTTONWIDGETMEDIATOR_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ButtonWidgetMediator : public QWidget
{
	Q_OBJECT
public:
	explicit ButtonWidgetMediator(QWidget *parent = 0);
	~ButtonWidgetMediator();
signals:

public slots:
	void penButton1Pressed();
	void penButton2Pressed();
private:
	QVBoxLayout *layout;

	QPushButton *handButton;
	QPushButton *penButton1;
	QPushButton *penButton2;
	QPushButton *rectButton;
	QPushButton *squareButton;
	QPushButton *circleButton;
	QPushButton *ellipseButton;
	QPushButton *triangleButton;


};

#endif // BUTTONWIDETMEDIATOR_H
