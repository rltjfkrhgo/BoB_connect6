#include "Mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QToolBar* toolBar = addToolBar(tr("toolBar"));

    QAction *newGameAction = new QAction(tr("&1:1"), this);
    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);
    toolBar->addAction(newGameAction);

    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
}

void MainWindow::newGame()
{
    statusBar()->showMessage("1:1");
}
