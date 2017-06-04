#include "templatecontrol.h"
#include "common.h"
#include <QMessageBox>

TemplateControl::TemplateControl(TemplateView *templateView,QObject *parent) : QObject(parent)
{
    templateViewIns = templateView;
    domDocument = new QDomDocument();
}

TemplateControl::~TemplateControl()
{

}

QStringList TemplateControl::readTemplateList()
{
    QStringList templateNmaes;
    QFile file(localSaveFileName);
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        if(!domDocument->setContent(&file))
        {
            file.close();
            initTemplateFile();
            return templateNmaes;
        }
        file.close();
        QDomElement root = domDocument->documentElement();
        if(root.tagName()=="xml")
        {
            QDomElement element = root.firstChildElement();
            while(!element.isNull())
            {
                if(element.tagName()=="template")
                {
                    templateNmaes.append(element.attribute("name"));
                }
                element = element.nextSiblingElement();
            }
        }
        return templateNmaes;
    }else{
        initTemplateFile();
        return templateNmaes;
    }

}

bool TemplateControl::saveTemplate(QString name)
{
    QFile file(localSaveFileName);
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        QDomElement root = domDocument->documentElement();
        if(root.tagName()=="xml")
        {
            QDomElement domElement = domDocument->createElement("template");
            root.appendChild(domElement);
            domElement.setAttribute("name",name);
            QStandardItem *item = templateViewIns->root();
            QModelIndex rootIndex= item->index();
            readTemplateViewLoop(domElement,rootIndex);
            domDocument->replaceChild(root,domDocument->documentElement());
            domDocument->save(out,4);
            return true;
        }
    }else{
        return false;
    }
    return false;
}

void TemplateControl::setFolderIcon(QIcon icon)
{
    folderIcon = icon;
}

bool TemplateControl::exportTemplate(QString filePath,QString templateName)
{
    QDomDocument *exportDoc = new QDomDocument();
    QFile file(filePath);
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        QDomElement root = exportDoc->createElement("xml");
        QDomElement domElement = exportDoc->createElement("template");
        root.appendChild(domElement);
        domElement.setAttribute("name",templateName);
        QStandardItem *item = templateViewIns->root();
        QModelIndex rootIndex= item->index();
        readTemplateViewLoop(domElement,rootIndex);
        exportDoc->appendChild(root);
        exportDoc->save(out,4);
        return true;
    }else{
        return false;
    }
}

bool TemplateControl::importTemplate(QString filePath)
{
    QFile file(filePath);
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QDomDocument *importDoc = new QDomDocument();
        if(!importDoc->setContent(&file))
        {
            file.close();
            QMessageBox::information(qobject_cast<QWidget*>(this->parent()),"","Invalid save file",QMessageBox::Yes);
            return false;
        }
        file.close();
        QDomElement root = importDoc->documentElement();
        if(root.tagName()=="xml")
        {
            QDomElement element = root.firstChildElement("template");
            templateViewIns->selectAll();
            templateViewIns->deleteFolder();
            QStandardItem *item =  templateViewIns->root();
            readTemplateFileLoop(element,*item);
            templateViewIns->previewUpdate();
            return true;
        }else{
            QMessageBox::information(qobject_cast<QWidget*>(this->parent()),"","Invalid save file",QMessageBox::Yes);
            return false;
        }
    }else{
        return false;
    }
}


void TemplateControl::loadTemplate(QString templateName)
{
    QDomElement root = domDocument->documentElement();
    if(root.tagName()=="xml")
    {
        QDomElement element = root.firstChildElement();
        while(!element.isNull())
        {
            if(element.tagName()=="template")
            {
                if(element.attribute("name") == templateName)
                {
                    break;
                }
            }
            element = element.nextSiblingElement();
        }
        templateViewIns->selectAll();
        templateViewIns->deleteFolder();
        QStandardItem *item =  templateViewIns->root();
        readTemplateFileLoop(element,*item);
        templateViewIns->previewUpdate();
    }
}

void TemplateControl::deleteTemplate(QString templateName)
{
    QFile file(localSaveFileName);
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        QDomElement root = domDocument->documentElement();
        if(root.tagName()=="xml")
        {
            QDomElement element= root.firstChildElement();
            while(!element.isNull())
            {
                if(element.tagName()=="template")
                {
                    if(element.attribute("name") == templateName)
                    {
                        break;
                    }
                }
                element = element.nextSiblingElement();
            }
            root.removeChild(element);
            domDocument->replaceChild(root,domDocument->documentElement());
            domDocument->save(out,4);
        }
    }
}

void TemplateControl::readTemplateViewLoop(QDomElement &templateElement,QModelIndex &index)
{
    bool hasChildren = templateViewIns->model()->hasChildren();
    if(hasChildren)
    {
        int count = templateViewIns->model()->rowCount(index);
        for(int i=0;i<count;i++){
            QModelIndex childrenIndex = templateViewIns->model()->index(i,0,index);
            QString data = templateViewIns->data(childrenIndex,Qt::DisplayRole).toString();
            QDomElement element = domDocument->createElement("folder");
            element.setAttribute("name",data);
            QStringList sequenceName = isSequencName(data);
            if(sequenceName.count()!=0)
            {
                element.setAttribute("start",templateViewIns->data(childrenIndex,Qt::UserRole+1).toInt());
                element.setAttribute("count",templateViewIns->data(childrenIndex,Qt::UserRole+2).toInt());
                element.setAttribute("step",templateViewIns->data(childrenIndex,Qt::UserRole+3).toInt());
            }
            templateElement.appendChild(element);
            readTemplateViewLoop(element,childrenIndex);
        }
    }
}

void TemplateControl::readTemplateFileLoop(QDomElement &templateElement,QStandardItem &parentItem)
{
    QDomElement element =  templateElement.firstChildElement();
    while(!element.isNull())
    {
        if(element.tagName() == "folder")
        {
            QString folderName = element.attribute("name");
            QStandardItem *item = new QStandardItem(folderName);
            item->setIcon(folderIcon);
            QStringList sequenceName =isSequencName(folderName);
            if(sequenceName.count()!=0)
            {
                item->setData(element.attribute("start"),Qt::UserRole+1);
                item->setData(element.attribute("count"),Qt::UserRole+2);
                item->setData(element.attribute("step"),Qt::UserRole+3);
            }
            readTemplateFileLoop(element,*item);
            parentItem.appendRow(item);
        }
        element = element.nextSiblingElement();
    }
}

void TemplateControl::initTemplateFile()
{
    QFile file(localSaveFileName);
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        domDocument->clear();
        QDomElement root = domDocument->createElement("xml");
        domDocument->appendChild(root);
        domDocument->save(out,4);
        file.close();
    }
}


