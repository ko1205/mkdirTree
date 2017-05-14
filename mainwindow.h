#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
//#include <QTreeView>
#include <QSplitter>
#include <QComboBox>
#include <QStatusBar>
#include <QMainWindow>
#include <QApplication>
#include "templateview.h"
#include "preview.h"


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
    QAction *createAct;
    QAction *deleteAct;

    QLineEdit *rootPathEdit;
    QPushButton *rootPathButton;

    TemplateView *templateView;
    PreView *preView;


    QPushButton *testButton;

    QPushButton *cancelButton;
    QPushButton *makeTreeButton;


private slots:
    void selectDiractory();
    void newProject();
    void createFolder();
    void deleteFolder();
    void testSlot();


};

#endif // MAINWINDOW_H
