#include "propertyview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "common.h"

PropertyView::PropertyView(QWidget *parent) : QWidget(parent)
{
    createForm();
    connect(startNumEdit,SIGNAL(valueChanged(int)),this,SLOT(setStart(int)));
    connect(countNumEdit,SIGNAL(valueChanged(int)),this,SLOT(setCount(int)));
    connect(stepNumEdit,SIGNAL(valueChanged(int)),this,SLOT(setStep(int)));
    connect(folderNameEdit,SIGNAL(textChanged(QString)),this,SLOT(checkFolderName(QString)));
}

PropertyView::~PropertyView()
{

}

void PropertyView::createForm()
{
    QVBoxLayout *baseLayout = new QVBoxLayout;
    QHBoxLayout *folderNameLayout = new QHBoxLayout;
    QHBoxLayout *startCountLayout = new QHBoxLayout;
    QHBoxLayout *stepLayout = new QHBoxLayout;

    folderNameLabel = new QLabel("FolderName");
    folderNameEdit = new QLineEdit();
    folderNameEdit->setEnabled(false);

    startNumLabel = new QLabel("Start");
    startNumEdit = new QSpinBox();
    startNumEdit->setRange(0,999999);
    startNumEdit->setEnabled(false);

    countNumLabel = new QLabel("Count");
    countNumEdit = new QSpinBox();
    countNumEdit->setRange(0,999999);
    countNumEdit->setEnabled(false);

    stepNumLabel = new QLabel("Step");
    stepNumEdit = new QSpinBox();
    stepNumEdit->setRange(0,999999);
    stepNumEdit->setEnabled(false);

    folderNameLayout->addWidget(folderNameLabel);
    folderNameLayout->addWidget(folderNameEdit);

    startCountLayout->addStretch();
    startCountLayout->addWidget(startNumLabel);
    startCountLayout->addWidget(startNumEdit);
    startCountLayout->addWidget(countNumLabel);
    startCountLayout->addWidget(countNumEdit);

    stepLayout->addStretch();
    stepLayout->addWidget(stepNumLabel);
    stepLayout->addWidget(stepNumEdit);

    baseLayout->addLayout(folderNameLayout);
    baseLayout->addLayout(startCountLayout);
    baseLayout->addLayout(stepLayout);
    baseLayout->addStretch();

    setLayout(baseLayout);
    setMaximumWidth(this->sizeHint().width());
}

void PropertyView::resetNumValue()
{
    startNumEdit->setRange(0,999999);
    startNumEdit->setValue(0);
    startNumEdit->setEnabled(false);

    countNumEdit->setRange(0,999999);
    countNumEdit->setValue(0);
    countNumEdit->setEnabled(false);

    stepNumEdit->setRange(0,999999);
    stepNumEdit->setValue(0);
    stepNumEdit->setEnabled(false);
}

void PropertyView::setCurrentItem(QStandardItem *item)
{
    currentItem = item;
    QString data = item->data(Qt::DisplayRole).toString();
    folderNameEdit->setText(data);
    if(isSequencName(data).count()!=0)
    {
        startNumEdit->setValue(item->data(Qt::UserRole+1).toInt());
        startNumEdit->setEnabled(true);
        startNumEdit->setRange(0,999999);

        countNumEdit->setValue(item->data(Qt::UserRole+2).toInt());
        countNumEdit->setEnabled(true);
        countNumEdit->setRange(1,999999);

        stepNumEdit->setValue(item->data(Qt::UserRole+3).toInt());
        stepNumEdit->setEnabled(true);
        stepNumEdit->setRange(1,999999);

    }else{
        resetNumValue();
    }
//    folderNameEdit->setEnabled(true);
//    QMessageBox::information(this,"",data,QMessageBox::Yes);
}

void PropertyView::resetAllData()
{
    currentItem = NULL;
    folderNameEdit->setText("");
    resetNumValue();
}

void PropertyView::setStart(int value)
{
    QString currentName=currentItem->data(Qt::DisplayRole).toString();
    if((isSequencName(currentName).count()!=0) && (currentItem->data(Qt::UserRole+1).toInt()!=value))
    {
        currentItem->setData(value,Qt::UserRole+1);

    }
}

void PropertyView::setCount(int value)
{
    QString currentName=currentItem->data(Qt::DisplayRole).toString();
    if((isSequencName(currentName).count()!=0) && (currentItem->data(Qt::UserRole+2).toInt()!=value))
    {
        currentItem->setData(value,Qt::UserRole+2);

    }
}

void PropertyView::setStep(int value)
{
    QString currentName=currentItem->data(Qt::DisplayRole).toString();
    if((isSequencName(currentName).count()!=0) && (currentItem->data(Qt::UserRole+3).toInt()!=value))
    {
        currentItem->setData(value,Qt::UserRole+3);

    }
}

void PropertyView::checkFolderName(QString folderName)
{

}
