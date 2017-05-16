#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>

class PropertyView : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyView(QWidget *parent = 0);
    ~PropertyView();

    QLabel *folderNameLabel;
    QLabel *startNumLabel;
    QLabel *countNumLabel;
    QLabel *stepNumLabel;
    QLineEdit *folderNameEdit;
    QSpinBox *startNumEdit;
    QSpinBox *countNumEdit;
    QSpinBox *stepNumEdit;


signals:

public slots:

private:
    void createForm();
};

#endif // PROPERTYVIEW_H
