#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include <QComboBox>
#include <QStatusBar>
#include <QMainWindow>
#include <QApplication>
#include "templateview.h"
#include "preview.h"
#include "propertyview.h"
#include "templatecontrol.h"
#include <QListWidget>
#include <QDialog>
#include <QDir>

class DeleteTemplateDialog : public QDialog
{
    Q_OBJECT
public:
    DeleteTemplateDialog(QWidget *parent = 0);
    ~DeleteTemplateDialog();
    void setTemplateList(QStringList list,QComboBox *combBox);

signals:
    void clickDelete(QString name);

private:

    QListWidget *templateList;
    QPushButton *deleteButton;
    QPushButton *cancelButton;
    QComboBox *templateListComboIns;
private slots:
    void deletTemplate();

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void deleteTemplateName(QString templateName);

private:
    void setWindow();
    void createActions();
    void createMenus();
    void createStatusBar();
    void createCentralWidget();
    void makefolderLoop(QModelIndex parentIndex,QDir rootDir);

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *newAct;
    QAction *saveTemplateAct;
    QAction *deleteTemplateAct;
    QAction *exportTemplateAct;
    QAction *importTemplateAct;
    QAction *createAct;
    QAction *deleteAct;
    QAction *expandAllAct;
    QAction *collapseAllAct;

    QLineEdit *rootPathEdit;
    QPushButton *rootPathButton;

    QComboBox *templateList;

    TemplateView *templateView;
    PreView *preView;
    PropertyView *propertyView;

    QPushButton *cancelButton;
    QPushButton *makeTreeButton;

    TemplateControl *templateControl;


private slots:
    void selectDiractory();
    void newProject();
    void saveTemplate();
    void deleteTemplate();
    void createFolder();
    void deleteFolder();
    void expandAll();
    void collapseAll();
    void makeFolderTree();
    void testSlot();


};

#endif // MAINWINDOW_H
