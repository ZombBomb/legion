#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->i_FSTEMode->setStyleSheet("QPushButton {color: #55aaff;}");
    ui->i_FETSMode->setStyleSheet("QPushButton {color: #55aaff;}");
    ui->i_ConvMode->setStyleSheet("QPushButton {color: #55aaff;}");
    ui->i_defMask->setFocus();

    //connect(ui->getClientFile,SIGNAL(clicked()),this,SLOT(fillClientFile()));
    //connect(ui->defMaskLine,SIGNAL(returnPressed()),this,SLOT(findDefines()));
    //connect(ui->addSrcFile,SIGNAL(returnPressed()),this,SLOT(addSrcFile()));
   //connect(ui->getSrcFile,SIGNAL(clicked()),this,SLOT(fillSorceFile()));
    //onnect(ui->conSrc,SIGNAL(clicked()),this,SLOT(convertProcess()));
   //connect(ui->nameOfExelFile,SIGNAL(returnPressed()),this,SLOT(setExelFileName()));
}

//функция вызывается при нажатии кнопки "Get client file", тут проходит весь процесс по получению клиентского файла
void Widget::fillClientFile()
{
    bool res = true;
    FSTEProcess ProcObj;
    if(ui->i_minMsgLen->value()!= 0)
        ProcObj.minMsgSize = ui->i_minMsgLen->value();

    if(ui->i_maxMsgLen->value()!= 0)
        ProcObj.maxMsgSize = ui->i_maxMsgLen->value();

    //check src files
    tmpFileList = ui->i_inList->toPlainText().split('\n', QString::SkipEmptyParts);
    if(!checkFileListFiles())
    {
        res = false;
    }
    else
    {
    ui->i_inList->clear();
    for(int i = 0; i < tmpFileList.size(); i++)
        ui->i_inList->append(tmpFileList.at(i));
    }

    //check defList
    if(!ui->i_defList->toPlainText().size())
    {
        res = false;
        ui->i_logList->append("Define list is empty");
    }
    else
    {
        ProcObj.defsList = ui->i_defList->toPlainText().split("\n", QString::SkipEmptyParts);
        ProcObj.curDefsMask = ui->i_defMask->text();
    }
    //start process
    if(res)
    {
            //add rall all src files
        QStringList filesList = ui->i_inList->toPlainText().split("\n",QString::SkipEmptyParts);
        ui->i_logList->append(ProcObj.runFSTEProcess(filesList, this));
    }
}

//функция вызывается при нажатии кнопки "Get sorce file", тут проходит весь процесс по заполнению всех исходных файлов
void Widget::fillSorceFile()
{
    bool res = true;

    //check xls files
    tmpFileList = ui->i_inList->toPlainText().split('\n', QString::SkipEmptyParts);
    if(!checkFileListFiles())
    {
        res = false;
    }
    else
    {
        ui->i_inList->clear();
        for(int i = 0; i < tmpFileList.size(); i++)
            ui->i_inList->append(tmpFileList.at(i));
    }

    //проверка соответствующих src файлов
    for(int i = 0; i< tmpFileList.size(); i++)
    {
        tmpFileList[i] = tmpFileList[i].split(".").at(0)+".c";
    }
    if(!checkFileListFiles())
        res = false;

    //start process
    if(res)
    {
        FETSProcess ProcObj;

        //setGuiStatus(false);

        QStringList strList=ui->i_inList->toPlainText().split('\n');
        for(int i = 0; i < strList.size(); i++)
        {
            ui->i_logList->append(ProcObj.getDataFromExcel( strList.at(i), this));
            ui->i_logList->append(ProcObj.setDataIntoSrc(tmpFileList.at(i)));
        }
        //setGuiStatus(true);
    }

    ui->i_logList->setFocus();
    //ui->getSrcFile->setDefault(false);

}

//проверяет существование исходных файлов из списка, оставляет существующие
bool Widget::checkFileListFiles()
{
    bool res = true;
     //проверяем на наличие файлы из списка
     if(tmpFileList.length()>0)
     {
         for(int i = 0; i < tmpFileList.size(); i++)
         {
             if(!QFile::exists("InOutArea/"+tmpFileList.at(i)))
             {
                 res = false;
                 ui->i_logList->append("Can`t find file:"+tmpFileList.at(i));
                 tmpFileList.removeAt(i);
             }
         }
     }
     return res;
}

//вызывается при нажати клафиши "Enter" в строке "Soft mask", активирует процесс поиска дефайнов //возможно больше не нужна
void Widget::findDefines()
{
    ui->i_defList->clear();
    if(ui->i_needDefUpdFlag->isChecked())
    {
        ui->i_logList->append( "Wait for finish process of update difanes!");
        updateDefines();
        ui->i_needDefUpdFlag->setChecked(false);
    }
    if(ui->i_defMask->text() != "")
        ui->i_logList->append(getDefinesFromXls(ui->i_defMask->text()));

    //ui->nameOfExelFile->setFocus();
}


Widget::~Widget()
{
    delete ui;
}

//вызывается при нажати клафиши "Enter" в строке "Src file name", добавляет исходный файлв с писок, и проверяет список
void Widget::addSrcFile()
{
    ///if(ui->addSrcFile->text()!="")
    {
        ui->i_inList->append("");//ui->addSrcFile->text());
    }
    //else
    {
        //ищем в дирректории программы файлы по маске "*.с*"
        QDir dir(QCoreApplication::applicationDirPath()+"/InOutArea");
        QFileInfoList dirContent = dir.entryInfoList(QDir::Files);
        for(int i = 0; i<dirContent.length(); i++)
        {
            if(dirContent.at(i).fileName().indexOf(".c")>=0)
            {
               ui->i_inList->append(dirContent.at(i).fileName());
            }
        }
    }

    if(ui->i_defMask->text() == "")
    {
        //ui->getSrcFile->setFocus();
      //  ui->getSrcFile->setDefault(true);
    }
    else
    {
      //  ui->getClientFile->setFocus();
     //   ui->getClientFile->setDefault(true);
    }
}


//достает из def.xls дефайны подходящие по маске софта
QString Widget::getDefinesFromXls(QString softMaskStr)
{
    QFile defineOrder("Config\\DefineOrder.txt");
    QStringList allDefs;
    QString tmpString;

    if(defineOrder.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        tmpString = defineOrder.readLine();
        allDefs = tmpString.split("\t");
        defineOrder.close();
    }

    QFile defProcessOutput("ProcessOutPut.txt");
    if(defProcessOutput.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QStringList currentClientDefsList;
        QString tmpDefsString;
        while(!defProcessOutput.atEnd())
        {
            currentClientDefsList.clear();
            tmpString.clear();
            tmpString = defProcessOutput.readLine();
            currentClientDefsList = tmpString.split("\t");

            if(currentClientDefsList.at(0).indexOf(softMaskStr)>=0)
            {
              tmpDefsString.clear();
              for(int j = 1; j<currentClientDefsList.size(); j++)
              {
                  if(currentClientDefsList.at(j) == "+" && ui->i_defList->toPlainText().indexOf(allDefs.at(j-1))<0)
                  {
                      ui->i_defList->append(allDefs.at(j-1));
                  }
              }
            }
        }
        defProcessOutput.close();
    }
return "Defines successfuly readed";
}

void Widget::setExelFileName()
{
   // if(ui->nameOfExelFile->text()!="")
    {
        ui->i_inList->append("");// ui->nameOfExelFile->text());
    }
   // else
    {
        //ищем в дирректории программы файлы по маске "*.xls*"
        QDir dir(QCoreApplication::applicationDirPath()+"/InOutArea");
        QFileInfoList dirContent = dir.entryInfoList(QDir::Files);
        for(int i = 0; i<dirContent.length(); i++)
        {
            if(dirContent.at(i).fileName().indexOf(".xls")>=0)
            {
               ui->i_inList->append(dirContent.at(i).fileName());
            }
        }
    }

    if(ui->i_defMask->text() == "")
    {
       // ui->getSrcFile->setFocus();
      //  ui->getSrcFile->setDefault(true);
    }
    else
    {
      //  ui->getClientFile->setFocus();
       // ui->getClientFile->setDefault(true);
    }
   // ui->addSrcFile->setFocus();
}

void Widget::updateDefines()
{
    QProcess process;
    process.start("java -jar ProjectDefines.jar");
    if (!process.waitForStarted())
        ui->i_logList->append( "ERROR:Process not start");
    if (!process.waitForFinished(-1))
        ui->i_logList->append( "ERROR:Process not finish");
    process.close();

    QFile newDefines("ProcessNewDefines.txt");
    if(newDefines.size()>0)
    {
        QStringList defsList;
        QString tmpString;

       if(newDefines.open(QIODevice::ReadOnly|QIODevice::Text))
       {
           while(!newDefines.atEnd())
           {
               tmpString.clear();
               tmpString +="\t";
               tmpString += newDefines.readLine();
               tmpString.remove("\n");
               defsList.push_back(tmpString);
           }
           newDefines.close();
       }

       QFile defineOrder("Config\\DefineOrder.txt");
       if(defineOrder.open(QIODevice::Append|QIODevice::Text))
       {
           QTextStream stream(&defineOrder);
           for(int j = 0; j < defsList.size(); j++)
               stream<<defsList.at(j);
           stream.flush();
           defineOrder.close();
       }

        process.start("java -jar ProjectDefines.jar");
        if (!process.waitForStarted())
            ui->i_logList->append( "ERROR:Process not start");
        if (!process.waitForFinished(-1))
            ui->i_logList->append( "ERROR:Process not finish");
        process.close();
    }
        ui->i_logList->append( "Process update defines finish");
}

void Widget::convertProcess()
{
    bool res = true;

    //check src files
    tmpFileList = ui->i_inList->toPlainText().split('\n', QString::SkipEmptyParts);
    if(!checkFileListFiles())
    {
        res = false;
    }
    else
    {
    ui->i_inList->clear();
    for(int i = 0; i < tmpFileList.size(); i++)
        ui->i_inList->append(tmpFileList.at(i));
    }

    //start process
    if(res)
    {
        for(int i = 0; i < tmpFileList.size(); i++)
        {
            ui->i_logList->append(convertFile(tmpFileList.at(i)));
        }
        //setGuiStatus(true);
    }

    //ui->logText->setFocus();
   // ui->getSrcFile->setDefault(false);


}

//!!need rewrite for own class
QString Widget::convertFile(QString fileName)
{
    QString InOutPath = "InOutArea";
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1257");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    QString curString;
    QString filePath = InOutPath+"/"+fileName;
    QFile srcFile(filePath);
    QStringList listOfData;
    listOfData.clear();



    if(!srcFile.open(QIODevice::ReadOnly|QIODevice::Text))return "Can`t open for read sorce file: "+fileName;
    while(!srcFile.atEnd())
    {
        curString.clear();
        curString = srcFile.readLine();
        ui->i_logList->append(curString);
        listOfData.push_back(curString);
    }
    srcFile.close();

    if(!srcFile.open(QIODevice::WriteOnly|QIODevice::Text))return "Can`t open for write sorce file: "+fileName;
    QTextStream stream(&srcFile);
    stream.setCodec("Windows-1257");
    for(int j = 0; j < listOfData.size(); j++)
        stream<<listOfData.at(j);
    stream.flush();
    srcFile.close();
    return "Sorce file successfuly converted: "+fileName;
}
