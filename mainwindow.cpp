#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgraphicsitemfactory.h"
#include "commands.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	QGraphicsItemFactory factory;

	ui->setupUi(this);
	ui->graphicsView->setScene(ui->widget->getScene());
	ui->graphicsView->setMouseTracking(true);

	ui->widget->registerCommand("Select", new CommandSelect());
	ui->widget->registerCommand("Move", new CommandMove());
	ui->widget->registerCommand("Remove", new CommandRemove());
	ui->widget->registerCommand("Group", new CommandGroup());
	ui->widget->registerCommand("Enlarge", new CommandEnlarge());
	ui->widget->registerCommand("Reduce", new CommandReduce());

	for (QString& uid : factory.getUids()) {
		ui->widget->registerCommand(uid, new CommandGraphicsItem(uid));
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}
