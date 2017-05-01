#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>
#include <QSplitter>
#include <QComboBox>
#include <QStatusBar>
#include <QMainWindow>
#include <QApplication>
#include "templateview.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setWindow();
    void createMenu();
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


    QPushButton *testButton;

    QPushButton *cancelButton;
    QPushButton *makeTreeButton;


private slots:
    void selectDiractory();
    void newProject();
    void testSlot();


};

#endif // MAINWINDOW_H
