#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindow();
    connect(newAct,SIGNAL(triggered(bool)),this,SLOT(newProject()));
    connect(createAct,SIGNAL(triggered(bool)),templateView,SLOT(insertFolder()));
    connect(deleteAct,SIGNAL(triggered(bool)),templateView,SLOT(deleteFolder()));
    connect(rootPathButton,SIGNAL(clicked(bool)),this,SLOT(selectDiractory()));
    connect(cancelButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    connect(testButton,SIGNAL(clicked(bool)),this,SLOT(testSlot()));

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
    testButton = new QPushButton(tr("testButton"));

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


    rootPathEdit->setReadOnly(true);

}

void MainWindow::selectDiractory()
{
    QString folderName = QFileDialog::getExistingDirectory(this);
    if(folderName!=""){
        rootPathEdit->setText(folderName);
        QDir dirName(folderName);
        templateView->setRootFolderName(dirName.dirName());
//        rootPathEdit->setReadOnly(true);
    }

//    QPalette *palette = new QPalette();
//    palette->setColor(QPalette::Base,Qt::gray);
//    palette->setColor(QPalette::Text,Qt::darkGray);
//    rootPathEdit->setPalette(*palette);

}

void MainWindow::newProject()
{
    templateView->selectAll();
    templateView->deleteFolder();
    rootPathEdit->setText("");
    templateView->setRootFolderName("/");
}

void MainWindow::testSlot()
{
    QModelIndex index = templateView->currentIndex();
    QString data = templateView->data(index,Qt::DisplayRole).toString();
    QRegExp rx("\\[[a-zA-Z0-9]+\\]");
    QStringList list =data.split(rx);
    int pos = rx.indexIn(data);
    QStringList pattern = rx.capturedTexts();
    QMessageBox::information(this,"",data,QMessageBox::Yes);

//    QString str = "offsets: 1.23 .50 71.00 6.00";
//    QRegExp rx("\\d*\\.\\d+");    // primitive floating point matching
//    int count = 0;
//    int pos = 0;
//    while ((pos = rx.indexIn(str, pos)) != -1) {
//        ++count;
//        QStringList aa = rx.capturedTexts();
//        pos += rx.matchedLength();
//    }
}
