#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindow();
    connect(cancelButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(createAct,SIGNAL(triggered(bool)),templateView,SLOT(insertFolder()));
    connect(deleteAct,SIGNAL(triggered(bool)),templateView,SLOT(deleteFolder()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setWindow()
{

    createMenu();
    createStatusBar();
    createCentralWidget();

}

void MainWindow::createMenu()
{
    newAct = new QAction(tr("&New project"),this);
    createAct = new QAction(tr("createFolder"),this);
    deleteAct = new QAction(tr("deleteFolder"),this);
    fileMenu = menuBar()->addMenu(tr("&File"));
    editMenu = menuBar()->addMenu(tr("&Edit"));

    fileMenu->addAction(newAct);
    editMenu->addAction(createAct);
    editMenu->addAction(deleteAct);

    menuBar()->setNativeMenuBar(0);
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("ready"));
}

void MainWindow::createCentralWidget()
{
    QWidget *centerWidget = new QWidget();
    QVBoxLayout *baseLayout = new QVBoxLayout();
    QHBoxLayout *topLineLayout = new QHBoxLayout();
    QLabel *rootPathLabel = new QLabel(tr("rootPath"));
    rootPathEdit = new QLineEdit();
    rootPathButton = new QPushButton(tr("..."));
    QComboBox *templateList = new QComboBox();
    templateList->addItem(tr("<select template>"));
    templateList->addItem(tr("test"));

    QHBoxLayout *viewLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();


    templateView = new TemplateView();
    QTreeView *preView = new QTreeView();
    QSplitter *viewerSplitter = new QSplitter();
    QWidget *propertyView = new QWidget();
    QVBoxLayout *propertyLayout = new QVBoxLayout();
    QPushButton *testButton = new QPushButton();

    makeTreeButton = new QPushButton(tr("Make"));
    cancelButton = new QPushButton(tr("cancel"));

    topLineLayout->addWidget(rootPathLabel);
    topLineLayout->addWidget(rootPathEdit);
    topLineLayout->addWidget(rootPathButton);
    topLineLayout->addWidget(templateList);

    viewerSplitter->addWidget(templateView);
    viewerSplitter->addWidget(preView);
    viewLayout->addWidget(viewerSplitter);

    propertyView->setLayout(propertyLayout);
    propertyLayout->addWidget(testButton);
    viewLayout->addWidget(propertyView);

    buttonLayout->addWidget(makeTreeButton);
    buttonLayout->addWidget(cancelButton);

    baseLayout->addLayout(topLineLayout);
    baseLayout->addLayout(viewLayout);
    baseLayout->addLayout(buttonLayout);

    centerWidget->setLayout(baseLayout);
    setCentralWidget(centerWidget);
}
