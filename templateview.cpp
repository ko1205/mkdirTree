#include "templateview.h"
#include <QStandardItemModel>
#include <QIcon>
#include <QHeaderView>
#include <QStringList>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>


TemplateView::TemplateView()
{
    QIcon folderIcon;
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    QStandardItemModel *templateModel = new QStandardItemModel();
    QList<QStandardItem *> item;
    QStandardItem *baseItem = new QStandardItem("test");
    QStandardItem *baseItem2 = new QStandardItem("abc");
    QStandardItem *baseItem3 = new QStandardItem("dddd");
    QStandardItem *baseItem4 = new QStandardItem("qqqq");
    QStandardItem *baseItem5 = new QStandardItem("asdas");

    QStringList headerLabels;
    headerLabels<<tr("TemplateView");
    baseItem->setData("test2",Qt::UserRole + 1);
    baseItem->setEditable(0);
    baseItem->setData("testEdit",Qt::DisplayRole);
    this->setDragDropMode(QAbstractItemView::InternalMove);
    templateModel->setHorizontalHeaderLabels(headerLabels);
//    item<<baseItem4<<baseItem5;
    setModel(templateModel);
    baseItem->appendRow(baseItem2);
    templateModel->appendRow(baseItem);
    templateModel->appendRow(baseItem3);
//    templateModel->appendRow(item);
//    delete baseItem3;

    baseItem->appendRow(baseItem4);
//    baseItem->appendColumn(item);
    baseItem->setIcon(folderIcon);
    baseItem2->setIcon(folderIcon);
    baseItem3->setIcon(folderIcon);
    expandAll();
    setSortingEnabled(1);
    sortByColumn(0,Qt::AscendingOrder);
//    QObject::connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(showIndex()));
}

TemplateView::~TemplateView()
{

}

void TemplateView::showIndex()
{
    int row = this->currentIndex().row();
    QString data =this->currentIndex().data().toString();
    QMessageBox::information(this,"test",QString::number(row)+data,QMessageBox::Yes);
}
void TemplateView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *testMenu = new QMenu(this);
    QAction *test = new QAction("test",this);
    QAction *test2 = new QAction("test2",this);
    testMenu->addAction(test);
    testMenu->addAction(test2);
    testMenu->exec(event->globalPos());
}

