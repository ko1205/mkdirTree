#include "preview.h"

PreView::PreView(TemplateView *templateview,QWidget *parent)
    :QTreeView(parent)
{
    createFolderIcon();
    viewModel = new QStandardItemModel(this);
    QStandardItem *rootItem = new QStandardItem(tr("test_root"));
    rootItem->setIcon(folderIcon);
    setModel(viewModel);



    QStringList headerLabels;
    headerLabels<<tr("Preview");
    viewModel->setHorizontalHeaderLabels(headerLabels);

    templateViewIns = templateview;

    viewModel->appendRow(rootItem);

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    updatePreVew();

}

PreView::~PreView()
{

}

void PreView::createFolderIcon()
{
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
}

void PreView::updatePreVew()
{
    viewModel->removeRow(0,rootIndex());
    QModelIndex rootIndex = templateViewIns->rootIndex();
    QStandardItem *item = readModelLoop(rootIndex);
    viewModel->appendRow(item);
    expandAll();
}

QStandardItem * PreView::readModelLoop(QModelIndex &index,QStandardItem *parentItem)
{
    bool hasChildre = templateViewIns->model()->hasChildren(index);
    if(hasChildre)
    {
        int count = templateViewIns->model()->rowCount(index);
        QStandardItem *item;
        for(int i=0;i<count;i++)
        {
            QModelIndex childrenIndex = templateViewIns->model()->index(i,0,index);
            QString data = templateViewIns->data(childrenIndex,Qt::DisplayRole).toString();
            item = new QStandardItem(folderIcon,data);
            readModelLoop(childrenIndex,item);
            if(parentItem){
                parentItem->appendRow(item);
            }
        }
        return item;
    }

}
