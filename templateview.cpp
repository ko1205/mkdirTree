#include "templateview.h"
#include <QMessageBox>

TemplateView::TemplateView()
{

    templateModel = new QStandardItemModel();

    QStringList headerLabels;
    headerLabels<<tr("TemplateView");
    templateModel->setHorizontalHeaderLabels(headerLabels);


    createFolderIcon();
    createRootFolder();

    setModel(templateModel);

    expandAll();
    setSortingEnabled(1);
    sortByColumn(0,Qt::AscendingOrder);
    setDragDropMode(QAbstractItemView::InternalMove);
//    setDragEnabled(1);
//    setDropIndicatorShown(1);
//    this->viewport()->acceptDrops();
//    setAcceptDrops(true);


    setSelectionMode(QAbstractItemView::ExtendedSelection);
    installEventFilter(this);

    popupMenu = new QMenu(this);
    insertAct = new QAction("insert",this);
    test2 = new QAction("test2",this);
    popupMenu->addAction(insertAct);
    popupMenu->addAction(test2);

    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(storOldName(QModelIndex)));
    connect(templateModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(checkRename(QModelIndex)));
    connect(insertAct,SIGNAL(triggered(bool)),this,SLOT(insert()));
    connect(templateModel,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(activeStor(QModelIndex,int ,int)));
}

TemplateView::~TemplateView()
{

}

void TemplateView::createFolderIcon()
{
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
}

void TemplateView::createRootFolder()
{
    rootItem = new QStandardItem(tr("/"));
    rootItem->setIcon(folderIcon);
    templateModel->appendRow(rootItem);
    rootItem->setEditable(false);
}

void TemplateView::showIndex()
{
    int row = this->currentIndex().row();
    QString data =this->currentIndex().data().toString();
    QMessageBox::information(this,"test",QString::number(row)+" "+data,QMessageBox::Yes);
}

void TemplateView::contextMenuEvent(QContextMenuEvent *event)
{
    popupMenu->exec(event->globalPos());
}

void TemplateView::insert()
{
    NewFolderName = QString(tr("NewFolder"));
    QStandardItem *newFolder = new QStandardItem(NewFolderName);
    newFolder->setIcon(folderIcon);
    QModelIndex index= currentIndex();

    if(templateModel->hasChildren(index))
    {
        QString autoReName = autoRename(NewFolderName,index);
        newFolder->setData(autoReName,Qt::DisplayRole);
    }
    if(index==rootIndex())
    {
        templateModel->appendRow(newFolder);
    }else{
        templateModel->itemFromIndex(index)->appendRow(newFolder);
    }
}

void TemplateView::setRootFolderName(const QString &rootName)
{
    rootItem->setData(rootName,Qt::DisplayRole);
}

bool TemplateView::hasSameName(QString folderName,QModelIndex &parent)
{
    bool isSameNam=false;
    int count = templateModel->rowCount(parent);
    QModelIndex childIndex;
    QString data;
    for(int i=0;i<count;i++)
    {
        childIndex = templateModel->index(i,0,parent);
        data = templateModel->data(childIndex,Qt::DisplayRole).toString();
        if(folderName == data)
        {
            isSameNam = true;
        }
    }
    return isSameNam;
}

bool TemplateView::hasSameName(const QModelIndex &index,QString folderName,QModelIndex &parent)
{
    bool isSameNam=false;
    int count = templateModel->rowCount(parent);
    QModelIndex childIndex;
    QString data;

    for(int i=0;i<count;i++)
    {
        childIndex = templateModel->index(i,0,parent);
        QString data = templateModel->data(childIndex,Qt::DisplayRole).toString();
        if(folderName == data)
        {
            if(index.row()!=i)
            {
                isSameNam = true;
            }
        }
    }
    return isSameNam;
}

QString TemplateView::autoRename(QString folderName,QModelIndex &parent,int addNum)
{
    if(hasSameName(folderName,parent))
    {
        QString autoFolderName;
        addNum++;
        autoFolderName = NewFolderName+QString::number(addNum);
        folderName = autoRename(autoFolderName,parent,addNum);
    }
    return folderName;
}

void TemplateView::storOldName(const QModelIndex &index)
{
    oldName = templateModel->data(index,Qt::DisplayRole).toString();
}

void TemplateView::checkRename(const QModelIndex &index)
{
    QModelIndex parent = templateModel->parent(index);
    QString newName = templateModel->data(index,Qt::DisplayRole).toString();
    if(hasSameName(index,newName,parent))
    {
        templateModel->setData(index,oldName,Qt::DisplayRole);
        QMessageBox::information(this,tr("Information"),tr("already have the same name"),QMessageBox::Yes);
    }
}

void TemplateView::activeStor(const QModelIndex &index,int start,int end)
{
    QString data = templateModel->data(index,Qt::DisplayRole).toString();
//    QMessageBox::information(this,"TEST",data+" "+QString::number(start)+" "+QString::number(end),QMessageBox::Yes);
}

bool TemplateView::eventFilter(QObject *object, QEvent *event)
{
    return QTreeView::eventFilter(object,event);
}

void TemplateView::dropEvent(QDropEvent *event)
{
//    QMessageBox::information(this,"test","dropEvent",QMessageBox::Yes);
//    QStringList SList = event->mimeData()->formats();
//    QByteArray testaa =  event->mimeData()->data("application/x-qabstractitemmodeldatalist");
//    foreach(QString a, SList)
//    {
//        QMessageBox::information(this,"test",data,QMessageBox::Yes);
//    }

    QModelIndexList selectList = selectedIndexes();
//    foreach(QModelIndex index ,selectList)
//    {
//        QString selectedItem = templateModel->data(index,Qt::DisplayRole).toString();
//        QMessageBox::information(this,"test",selectedItem,QMessageBox::Yes);
//    }
    QModelIndex index;
        // rootIndex() (i.e. the viewport) might be a valid index

    if (viewport()->rect().contains(event->pos())) {
        index = indexAt(event->pos());
        if (!index.isValid() || !visualRect(index).contains(event->pos()))
            index = rootIndex();
    }
    QMessageBox::information(this,"",templateModel->data(index,Qt::DisplayRole).toString(),QMessageBox::Yes);

//    QTreeView::dropEvent(event);
}
