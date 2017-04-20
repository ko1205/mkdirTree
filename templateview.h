#ifndef TEMPLATEVIEW_H
#define TEMPLATEVIEW_H

#include <QTreeView>

class TemplateView : public QTreeView
{
    Q_OBJECT

public:
    TemplateView();
    ~TemplateView();
    void contextMenuEvent(QContextMenuEvent *event);
public slots:
    void showIndex();

};

#endif // TEMPLATEVIEW_H
