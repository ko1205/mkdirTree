#include "mainwindow.h"
#include "common.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

DeleteTemplateDialog::DeleteTemplateDialog(QWidget *parent)
    : QDialog(parent)
{
    templateList = new QListWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    deleteButton = new QPushButton("Delete");
    cancelButton = new QPushButton("Cancel");

    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(cancelButton);
    layout->addWidget(templateList);
    layout->addLayout(buttonLayout);
    setLayout(layout);

    connect(deleteButton,SIGNAL(clicked(bool)),this,SLOT(deletTemplate()));
    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
DeleteTemplateDialog::~DeleteTemplateDialog()
{

}

void DeleteTemplateDialog::setTemplateList(QStringList list,QComboBox *combBox)
{
    templateList->addItems(list);
    templateListComboIns = combBox;
}

void DeleteTemplateDialog::deletTemplate()
{
    QString templateName = templateList->currentItem()->data(Qt::DisplayRole).toString();
    emit clickDelete(templateName);
    QListWidgetItem *item = templateList->currentItem();
    delete item;
    int index = templateListComboIns->findText(templateName);
    templateListComboIns->removeItem(index);
//    templateList->removeItemWidget(item);
//    QMessageBox::information(this,"",templateName,QMessageBox::Yes);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindow();

    connect(rootPathButton,SIGNAL(clicked(bool)),this,SLOT(selectDiractory()));
    connect(templateList,SIGNAL(currentIndexChanged(QString)),templateControl,SLOT(loadTemplate(QString)));
    connect(templateView,SIGNAL(itemClickedView(QStandardItem*)),propertyView,SLOT(setCurrentItem(QStandardItem*)));
    connect(templateView,SIGNAL(itemDeleted()),propertyView,SLOT(resetAllData()));
    connect(makeTreeButton,SIGNAL(clicked(bool)),this,SLOT(makeFolderTree()));
    connect(cancelButton,SIGNAL(clicked()),qApp,SLOT(quit()));

//    connect(testButton,SIGNAL(clicked(bool)),this,SLOT(testSlot()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::setWindow()
{
    createActions();
    createMenus();
    createStatusBar();
    createCentralWidget();
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New project"),this);
    connect(newAct,SIGNAL(triggered(bool)),this,SLOT(newProject()));

    saveTemplateAct = new QAction(tr("Save Template"));
    connect(saveTemplateAct,SIGNAL(triggered(bool)),this,SLOT(saveTemplate()));

    deleteTemplateAct = new QAction(tr("delete Template"));
    connect(deleteTemplateAct,SIGNAL(triggered(bool)),this,SLOT(deleteTemplate()));

    exportTemplateAct = new QAction(tr("export Template"));
    connect(exportTemplateAct,SIGNAL(triggered(bool)),this,SLOT(exportTemplate()));

    importTemplateAct = new QAction(tr("import Template"));
    connect(importTemplateAct,SIGNAL(triggered(bool)),this,SLOT(importTemplate()));

    createAct = new QAction(tr("createFolder"),this);
    connect(createAct,SIGNAL(triggered(bool)),this,SLOT(createFolder()));

    deleteAct = new QAction(tr("deleteFolder"),this);
    connect(deleteAct,SIGNAL(triggered(bool)),this,SLOT(deleteFolder()));

    expandAllAct = new QAction("Expand All",this);
    connect(expandAllAct,SIGNAL(triggered(bool)),this,SLOT(expandAll()));

    collapseAllAct = new QAction("Collapse All",this);
    connect(collapseAllAct,SIGNAL(triggered(bool)),this,SLOT(collapseAll()));
}

void MainWindow::createMenus()
{

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveTemplateAct);
    fileMenu->addAction(deleteTemplateAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exportTemplateAct);
    fileMenu->addAction(importTemplateAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(createAct);
    editMenu->addAction(deleteAct);
    editMenu->addSeparator();
    editMenu->addAction(expandAllAct);
    editMenu->addAction(collapseAllAct);

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
    templateList = new QComboBox();
    templateList->addItem(tr("<select template>"));

    QHBoxLayout *viewLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();


    templateView = new TemplateView();
    preView = new PreView(templateView);
    templateView->connectPreView(preView);
    QSplitter *viewerSplitter = new QSplitter();
    propertyView = new PropertyView();

    templateControl = new TemplateControl(templateView);
    templateList->addItems(templateControl->readTemplateList());
    templateControl->setFolderIcon(templateView->icon());


    makeTreeButton = new QPushButton(tr("Make"));
    cancelButton = new QPushButton(tr("cancel"));

    topLineLayout->addWidget(rootPathLabel);
    topLineLayout->addWidget(rootPathEdit);
    topLineLayout->addWidget(rootPathButton);
    topLineLayout->addWidget(templateList);

    viewerSplitter->addWidget(templateView);
    viewerSplitter->addWidget(preView);

    viewLayout->addWidget(viewerSplitter);
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
    QString folderName = QFileDialog::getExistingDirectory(this,"set root path",QDir::home().path());
    if(folderName!=""){
        rootPathEdit->setText(folderName);
        QDir dirName(folderName);
        templateView->setRootFolderName(dirName.dirName());
    }
}

void MainWindow::newProject()
{
    templateView->selectAll();
    templateView->deleteFolder();
    rootPathEdit->setText("");
    templateView->setRootFolderName("/");
}

void MainWindow::saveTemplate()
{
    bool ok;
    int templateNameIndex;
    QString templateName = QInputDialog::getText(this,"Save Template","TemplateName",QLineEdit::Normal,"template",&ok);
     if (ok && !templateName.isEmpty())
     {
         if(templateList->findText(templateName)==-1)
         {
             disconnect(templateList,SIGNAL(currentIndexChanged(QString)),templateControl,SLOT(loadTemplate(QString)));
             if(templateControl->saveTemplate(templateName))
             {
                 templateList->addItem(templateName);
                 templateNameIndex = templateList->findData(templateName,Qt::DisplayRole);
                 templateList->setCurrentIndex(templateNameIndex);
             }else{
                 QMessageBox::information(this,"","Save fales",QMessageBox::Yes);
             }
             connect(templateList,SIGNAL(currentIndexChanged(QString)),templateControl,SLOT(loadTemplate(QString)));
         }else{
             QMessageBox::information(this,"","already have the same template name",QMessageBox::Yes);
         }
     }
}

void MainWindow::deleteTemplate()
{
    DeleteTemplateDialog deleteTemplateWindow(this);
    deleteTemplateWindow.setTemplateList(templateControl->readTemplateList(),templateList);
    connect(&deleteTemplateWindow,SIGNAL(clickDelete(QString)),templateControl,SLOT(deleteTemplate(QString)));
    deleteTemplateWindow.exec();
}

void MainWindow::exportTemplate()
{
    bool ok;
    QString filePath = QFileDialog::getSaveFileName(this,"Export Template",QDir::home().path(),"XML files (*.xml)");
    QString templateName = QInputDialog::getText(this,"Save Template","TemplateName",QLineEdit::Normal,"template",&ok);
    if(!filePath.isEmpty() && ok && !templateName.isEmpty())
    {
        if(templateControl->exportTemplate(filePath,templateName))
        {
            QMessageBox::information(this,"","export completed",QMessageBox::Yes);
        }else{
            QMessageBox::information(this,"","Save fales",QMessageBox::Yes);
        }
    }
}

void MainWindow::importTemplate()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Import Template",QDir::home().path(),"XML files (*.xml)");
    if(!filePath.isEmpty())
    {
        if(templateControl->importTemplate(filePath))
        {
            saveTemplate();
        }else{
            QMessageBox::information(this,"","Import fales",QMessageBox::Yes);
        }
    }
//    QMessageBox::information(this,"","importTemplate Test",QMessageBox::Yes);
}

void MainWindow::createFolder()
{
    templateView->insertFolder();
}

void MainWindow::deleteFolder()
{
    templateView->deleteFolder();
}

void MainWindow::expandAll()
{
    templateView->expandAll();
}

void MainWindow::collapseAll()
{
    templateView->collapseAll();
    templateView->expand(templateView->root()->index());
}

void MainWindow::makeFolderTree()
{
    QString rootPaht = rootPathEdit->text();
    if(rootPaht!="")
    {
        QDir root(rootPaht);
        QString rootDirNmae = root.dirName();
        QModelIndex rootIndex = preView->model()->index(0,0,preView->rootIndex());
        if(preView->model()->data(rootIndex,Qt::DisplayRole).toString() == rootDirNmae)
        {
            makefolderLoop(rootIndex,root);
            QMessageBox::information(this,"information","folder create completed.",QMessageBox::Yes);
        }
    }else{
        QMessageBox::information(this,"Warning","set the root folder",QMessageBox::Yes);
    }
}

void MainWindow::makefolderLoop(QModelIndex parentIndex, QDir rootDir)
{
    bool hasChildren = preView->model()->hasChildren(parentIndex);
    if(hasChildren)
    {
        int count = preView->model()->rowCount(parentIndex);
        for(int i=0;i<count;i++)
        {
            QModelIndex index = preView->model()->index(i,0,parentIndex);
            QString data = preView->model()->data(index,Qt::DisplayRole).toString();
            rootDir.mkdir(data);
//            statusBar()->showMessage(rootDir.absolutePath()+"/"+data);
            QDir dir(rootDir);
            dir.cd(data);
            makefolderLoop(index,dir);
        }
    }
}

void MainWindow::testSlot()
{
    QModelIndex index = templateView->currentIndex();
    QString data = templateView->data(index,Qt::DisplayRole).toString();
    QRegExp rx("\\[[a-zA-Z0-9]+\\]");
    QStringList list =data.split(rx);
    int pos = rx.indexIn(data);
    QStringList pattern = rx.capturedTexts();

    if(isSequencName(data).count()!=0)
    {
        QMessageBox::information(this,"",data,QMessageBox::Yes);
    }

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
