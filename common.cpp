#include "common.h"
#include <QRegExp>
#include <QStringList>

bool isSequencName(QString folderName)
{
    QRegExp rx("#+");
    int pos = rx.indexIn(folderName);
    if(pos > -1)
    {
        QStringList list = folderName.split(rx);
        return true;
    }
    return false;
}
