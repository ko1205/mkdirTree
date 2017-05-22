#include "propertyview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

PropertyView::PropertyView(QWidget *parent) : QWidget(parent)
{
    createForm();
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
    startNumEdit->setMaximum(999999);
    startNumEdit->setEnabled(false);

    countNumLabel = new QLabel("Count");
    countNumEdit = new QSpinBox();
    countNumEdit->setMaximum(999999);
    countNumEdit->setEnabled(false);

    stepNumLabel = new QLabel("Step");
    stepNumEdit = new QSpinBox();
    stepNumEdit->setMaximum(999999);
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
    startNumEdit->setValue(0);
    startNumEdit->setEnabled(false);

    countNumEdit->setValue(0);
    countNumEdit->setEnabled(false);

    stepNumEdit->setValue(0);
    stepNumEdit->setEnabled(false);
}

void PropertyView::setCurrentItem(QStandardItem *item)
{
    currentItem = item;
    QString data = item->data(Qt::DisplayRole).toString();
    folderNameEdit->setText(data);
//    folderNameEdit->setEnabled(true);
//    QMessageBox::information(this,"",data,QMessageBox::Yes);
}

void PropertyView::resetAllData()
{
    currentItem = NULL;
    folderNameEdit->setText("");
    resetNumValue();
}

void PropertyView::checkFolderName(QString folderName)
{

}
