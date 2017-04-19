#include "mainwindow.h"
#include "templateview.h"
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>
#include <QSplitter>
#include <QComboBox>
#include <QStatusBar>


MainWindow::MainWindow(QApplication *app,QWidget *parent)
    : QMainWindow(parent)
{
    setWindow(app);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setWindow(QApplication *app)
{

    QMenu *fileMenu;
    QMenu *editMenu;
    QAction *newAction = new QAction(tr("&New project"),this);
    QAction *createFolder = new QAction(tr("CreateFolder"));
    fileMenu = menuBar()->addMenu(tr("&File"));
    editMenu = menuBar()->addMenu(tr("&Edit"));

    fileMenu->addAction(newAction);
    editMenu->addAction(createFolder);


    menuBar()->setNativeMenuBar(0);

    statusBar()->showMessage(tr("ready"));

    QWidget *centerWidget = new QWidget();
    QVBoxLayout *baseLayout = new QVBoxLayout();
    QHBoxLayout *topLineLayout = new QHBoxLayout();
    QLabel *rootPathLabel = new QLabel(tr("rootPath"));
    QLineEdit *rootPathEdit = new QLineEdit();
    QPushButton *rootPathButton = new QPushButton(tr("..."));
    QComboBox *templateList = new QComboBox();
    templateList->addItem(tr("<select template>"));

    QHBoxLayout *viewLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();


    TemplateView *templateView = new TemplateView();
    QTreeView *preView = new QTreeView();
    QSplitter *viewerSplitter = new QSplitter();
    QWidget *propertyView = new QWidget();
    QVBoxLayout *propertyLayout = new QVBoxLayout();
    QPushButton *testButton = new QPushButton();

    QPushButton *makeTreeButton = new QPushButton(tr("Make"));
    QPushButton *cancelButton = new QPushButton(tr("cancel"));

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

    QObject::connect(cancelButton,SIGNAL(clicked()),app,SLOT(quit()));

//    return 0;
}
