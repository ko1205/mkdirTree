#include "mainwindow.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindow();
}

MainWindow::~MainWindow()
{

}

int MainWindow::setWindow()
{
    QMenu *fileMenu;
    QAction *newAction = new QAction(tr("&New project"),this);
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu -> addAction(newAction);

    menuBar()->setNativeMenuBar(0);
    return 0;
}
