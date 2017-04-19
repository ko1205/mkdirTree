#include "mainwindow.h"
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindow();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setWindow()
{
    QMenu *fileMenu;
    QAction *newAction = new QAction(tr("&New project"),this);
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu -> addAction(newAction);

    menuBar()->setNativeMenuBar(0);

    QWidget *centerWidget = new QWidget();
    QVBoxLayout *baseLayout = new QVBoxLayout();
    QHBoxLayout *topLineLayout = new QHBoxLayout();
    QLabel *rootPathLabel = new QLabel(tr("rootPath"));
    QLineEdit *rootPathEdit = new QLineEdit();
    QPushButton *rootPathButton = new QPushButton(tr("..."));

    QHBoxLayout *viewLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();


    QTreeView *templateView = new QTreeView();
    QTreeView *preView = new QTreeView();

    QPushButton *makeTreeButton = new QPushButton(tr("Make"));
    QPushButton *cancelButton = new QPushButton(tr("cancel"));

    topLineLayout ->addWidget(rootPathLabel);
    topLineLayout ->addWidget(rootPathEdit);
    topLineLayout ->addWidget(rootPathButton);

    viewLayout->addWidget(templateView);
    viewLayout->addWidget(preView);

    buttonLayout->addWidget(makeTreeButton);
    buttonLayout->addWidget(cancelButton);

    baseLayout->addLayout(topLineLayout);
    baseLayout->addLayout(viewLayout);
    baseLayout->addLayout(buttonLayout);

    centerWidget->setLayout(baseLayout);
    setCentralWidget(centerWidget);

//    return 0;
}
