#ifndef PREVIEW_H
#define PREVIEW_H
#include <QTreeView>
#include <QStandardItemModel>
#include "templateview.h"


class PreView : public QTreeView
{
public:
    PreView(TemplateView *templateView,QWidget *parent=0);
    ~PreView();
    void updatePreVew();

private:
    void createFolderIcon();
    QStandardItem * readModelLoop(QModelIndex &index,QStandardItem *parentItem=0);


    QStandardItemModel *viewModel;
    QIcon folderIcon;
    TemplateView *templateViewIns;



};

#endif // PREVIEW_H
