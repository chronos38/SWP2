#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgraphicsitemfactory.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	/*
	m_scene = new GraphicsScene();
	ui->graphicsView->setScene(m_scene);
	ui->graphicsView->setMouseTracking(true);
	QGraphicsItemFactory factory;
	m_scene->addItem(factory.makeEllipse());
	m_scene->addItem(factory.makeCircle());
	m_scene->addItem(factory.makeTriangle());
	m_scene->addItem(factory.makeRect());
	for(auto &it: m_scene->items()) {
		it->setFlags(QGraphicsItem::ItemIsMovable);
	}
	*/
	ui->graphicsView->setScene(ui->widget->getScene());
	ui->graphicsView->setMouseTracking(true);

	ui->widget->registerCommand("Select", new CommandSelect());
	ui->widget->registerCommand("Move", new CommandMove());
	ui->widget->registerCommand("Remove", new CommandRemove());
	ui->widget->registerCommand("Group", new CommandGroup());

}

MainWindow::~MainWindow()
{
	if (m_scene) {
		delete m_scene;
	}

	delete ui;
}
