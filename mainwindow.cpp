#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgraphicsitemfactory.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->graphicsView->setScene(ui->widget->getScene());
	ui->graphicsView->setMouseTracking(true);

	ui->widget->registerCommand("Select", new CommandSelect());
	ui->widget->registerCommand("Move", new CommandMove());
	ui->widget->registerCommand("Remove", new CommandRemove());
	ui->widget->registerCommand("Group", new CommandGroup());
}

MainWindow::~MainWindow()
{
	delete ui;
}
