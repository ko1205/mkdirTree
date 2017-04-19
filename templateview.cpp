#include "templateview.h"
#include <QStandardItemModel>
#include <QIcon>
#include <QHeaderView>
#include <QStringList>


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
    templateModel->setHorizontalHeaderLabels(headerLabels);
//    item<<baseItem4<<baseItem5;
    setModel(templateModel);
    baseItem->appendRow(baseItem2);
    templateModel->appendRow(baseItem);
    templateModel->appendRow(baseItem3);
//    templateModel->appendColumn(item);
//    delete baseItem3;
    baseItem->setIcon(folderIcon);
    baseItem2->setIcon(folderIcon);
    baseItem3->setIcon(folderIcon);
    expandAll();
}

TemplateView::~TemplateView()
{

}
