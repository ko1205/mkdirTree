#include "mainwindow.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenu *fileMenu;
    QAction *newAction = new QAction(tr("&New project"),this);
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu -> addAction(newAction);

    menuBar()->setNativeMenuBar(0);
}

MainWindow::~MainWindow()
{

}
