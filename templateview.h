#ifndef TEMPLATEVIEW_H
#define TEMPLATEVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMimeData>

class PreView;
class TemplateView : public QTreeView
{
    Q_OBJECT

public:
    TemplateView(QWidget *parent = 0);
    ~TemplateView();
    QVariant data(const QModelIndex &index,int Role=Qt::EditRole) const;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void connectPreView(PreView *preview);


public slots:
    void showIndex();
    void insertFolder();
    void deleteFolder();
    void setRootFolderName(const QString &rootName);

private:
    bool hasSameName(QString folderName,QModelIndex &parent);
    bool hasSameName(const QModelIndex &index,QString folderName,QModelIndex &parent);
    QString autoRename(QString folderName,QModelIndex &parent,int addNum=0);
    void createFolderIcon();
    void createRootFolder();

    QStandardItemModel *templateModel;
    QStandardItem *rootItem;
    QMenu *popupMenu;
    QAction *insertAct;
    QAction *deleteAct;

    QIcon folderIcon;
    QString NewFolderName;
    QString oldName;
    PreView *previewIns;

private slots:
    void storOldName(const QModelIndex &index);
    void checkRename(const QModelIndex &index);
    void activeStor(const QModelIndex &index,int start,int end);
    void testClicked(const QModelIndex &index);
    void rowRemovedModel();

protected:
    void dropEvent(QDropEvent *event) override;
};

#endif // TEMPLATEVIEW_H
