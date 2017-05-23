#include "common.h"
#include <QRegExp>
#include <QStringList>
#include <QMessageBox>

QStringList isSequencName(QString folderName)
{
    QRegExp rx("#+");
    int pos = rx.indexIn(folderName);
    QStringList list = folderName.split(rx);
    if(pos > -1)
    {
        if(list.count()!=2)
        {
            QMessageBox::information(NULL,"","Invalid sequence name",QMessageBox::Yes);
            list.clear();
            return list;
        }else{
            list.insert(1,rx.capturedTexts()[0]);
            return list;
        }
    }
    list.clear();
    return list;
}
