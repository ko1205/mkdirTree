#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app, QWidget *parent = 0);
    ~MainWindow();

private:
    void setWindow(QApplication *app);
};

#endif // MAINWINDOW_H
