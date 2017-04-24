#include "templateview.h"
#include <QMessageBox>
#include <QShortcut>

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

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    installEventFilter(this);

    popupMenu = new QMenu(this);
    insertAct = new QAction("insert",this);
    deleteAct = new QAction("delete",this);
    popupMenu->addAction(insertAct);
    popupMenu->addAction(deleteAct);

    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(storOldName(QModelIndex)));
    connect(templateModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(checkRename(QModelIndex)));
    connect(insertAct,SIGNAL(triggered(bool)),this,SLOT(insertFolder()));
    connect(deleteAct,SIGNAL(triggered(bool)),this,SLOT(deleteFolder()));
    connect(shortcut,SIGNAL(activated()),this,SLOT(deleteFolder()));
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

void TemplateView::insertFolder()
{
    NewFolderName = QString(tr("NewFolder"));
    QStandardItem *newFolder = new QStandardItem(NewFolderName);
    newFolder->setIcon(folderIcon);
    QModelIndex index= currentIndex();
    if(index==rootIndex() || !index.isValid())
    {
        index = templateModel->indexFromItem(rootItem);
    }

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

void TemplateView::deleteFolder()
{
    QModelIndexList list = selectedIndexes();
    QList<QStandardItem*> items;
    items.clear();
    foreach (QModelIndex index, list)
    {
        if(rootItem!=templateModel->itemFromIndex(index))
        {
////////////////////////////////////////
/// 조건문 추가 필요 인덱스 중에 상위 인덱스가 포함되어 있으면 취소/////
/// //////
            items.append(templateModel->itemFromIndex(index));
        }
    }
    foreach (QStandardItem *item, items) {
        QModelIndex deleteIndex= templateModel->indexFromItem(item);
        QModelIndex parent = templateModel->parent(deleteIndex);
        int row = deleteIndex.row();
        templateModel->removeRow(row,parent);
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


void TemplateView::dropEvent(QDropEvent *event)
{
    QModelIndexList selectList = selectedIndexes();

    //////////////////////////////////////////////////////////////////
    /// \brief index
    /// private Class 의 DropOn 함수 기능 제정의
    ///////////////////////////////////////////////////////////////

    QModelIndex parent;
        // rootIndex() (i.e. the viewport) might be a valid index

    if (viewport()->rect().contains(event->pos())) {
        parent = indexAt(event->pos());
        if (!parent.isValid() || !visualRect(parent).contains(event->pos()))
            parent = rootIndex();
    }

    if(parent != rootIndex())
    {


        foreach(QModelIndex index ,selectList)
        {
            for(int i=0;i<selectList.size();i++)
            {
                if(index!=selectList[i])
                {
                    if(templateModel->data(index,Qt::DisplayRole).toString()==\
                            templateModel->data(selectList[i],Qt::DisplayRole).toString())
                    {
                        QMessageBox::information(this,tr("Information"),tr("selected Folder have same name"),QMessageBox::Yes);
                        return;
                    }
                }
            }
            QString selectedItem = templateModel->data(index,Qt::DisplayRole).toString();
            if(hasSameName(selectedItem,parent))
            {
                QMessageBox::information(this,tr("Information"),tr("already have the same name"),QMessageBox::Yes);
                return;
            }
        }
        QTreeView::dropEvent(event);
    }
    return;
//    QMessageBox::information(this,"test",selectedItem,QMessageBox::Yes);

//    QTreeView::dropEvent(event);
}
