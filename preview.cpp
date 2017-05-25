#include "preview.h"
#include "common.h"

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
    QStringList sequenceNames;
    QStandardItem *item;
    bool hasChildre = templateViewIns->model()->hasChildren(index);
    if(hasChildre)
    {
        int count = templateViewIns->model()->rowCount(index);
//        QStandardItem *item;
        for(int i=0;i<count;i++)
        {
            QModelIndex childrenIndex = templateViewIns->model()->index(i,0,index);
            QString data = templateViewIns->data(childrenIndex,Qt::DisplayRole).toString();
            sequenceNames = isSequencName(data);
            if(sequenceNames.count()!=0)
            {
                int startNum = templateViewIns->data(childrenIndex,Qt::UserRole+1).toInt();
                int countNum = templateViewIns->data(childrenIndex,Qt::UserRole+2).toInt();
                int stepNum = templateViewIns->data(childrenIndex,Qt::UserRole+3).toInt();
                for(int n=0;n<countNum;n++)
                {
                    int padding = sequenceNames[1].count();
//
                    QString formateName;
//                    formateName.sprintf((sequenceNames[0]+"%0"+QString::number(padding)+"d"+sequenceNames[2]).toStdString(),startNum+(countNum*stepNum));
                    formateName = sequenceNames[0]+"%1"+sequenceNames[2];
                    QString sequenceName=formateName.arg((startNum+(n*stepNum)),padding,10,QLatin1Char('0'));
                    item = new QStandardItem(folderIcon,sequenceName);
                    readModelLoop(childrenIndex,item);
                    if(parentItem){
                        parentItem->appendRow(item);
                    }

                }
            }else{
                item = new QStandardItem(folderIcon,data);
                readModelLoop(childrenIndex,item);
                if(parentItem){
                    parentItem->appendRow(item);
                }

            }
        }
        return item;
    }
    return item;
}
