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


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setWindow();
    void createActions();
    void createMenus();
    void createStatusBar();
    void createCentralWidget();

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *newAct;
    QAction *saveTemplateAct;
    QAction *deleteTemplateAct;
    QAction *exportTemplateAct;
    QAction *importTemplateAct;
    QAction *createAct;
    QAction *deleteAct;

    QLineEdit *rootPathEdit;
    QPushButton *rootPathButton;

    QComboBox *templateList;

    TemplateView *templateView;
    PreView *preView;
    PropertyView *propertyView;

    QPushButton *cancelButton;
    QPushButton *makeTreeButton;


private slots:
    void selectDiractory();
    void newProject();
    void saveTemplate();
    void createFolder();
    void deleteFolder();
    void testSlot();


};

#endif // MAINWINDOW_H
