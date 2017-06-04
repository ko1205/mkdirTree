#ifndef TEMPLATECONTROL_H
#define TEMPLATECONTROL_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QWidget>
#include "templateview.h"
#include <QApplication>

class TemplateControl : public QObject
{
    Q_OBJECT
public:
    explicit TemplateControl(TemplateView *templateView , QObject *parent = 0);
    ~TemplateControl();
    QStringList readTemplateList();
    bool saveTemplate(QString name);
    void setFolderIcon(QIcon icon);
    bool exportTemplate(QString filePath,QString templateName);
    bool importTemplate(QString filePath);

signals:

public slots:
    void loadTemplate(QString templateName);
    void deleteTemplate(QString templateName);

private:
    void readTemplateViewLoop(QDomElement &templateElement,QModelIndex &index);
    void readTemplateFileLoop(QDomElement &templateElement,QStandardItem &parentItem);
    void initTemplateFile();

    QDomDocument *domDocument;
    TemplateView *templateViewIns;
//    QString localSaveFileName = "template.xml";
    QString localSaveFileName = QApplication::applicationDirPath()+"/template.xml";
    QIcon folderIcon;
};

#endif // TEMPLATECONTROL_H
