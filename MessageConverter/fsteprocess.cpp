#include "fsteprocess.h"
#include <QDebug>
#define IGNORE_DEF  0
#define INCLUDE_DEF  1
const QString InOutPath = "InOutArea";

FSTEProcess::FSTEProcess()
{
    defsList.clear();
    outList.clear();
    tree.clear();
    minMsgSize = 0;
    maxMsgSize = 100;
}

QString FSTEProcess::runFSTEProcess(QStringList filesList, QWidget *widget)
{
    //make list with all defs
    makeAllDefsList();

    QString onlyName;
    for(int i = 0; i <filesList.size(); i++)
    {
        processingSorceFile(filesList.at(i));
        if(outList.size()>0)
        {
            onlyName = filesList[i].split(".").at(0);
            setDataIntoExcel( onlyName, widget);
        }
        outList.clear();
    }
    return "All ok";
}


//заполняет excel файл из внутренней структуры
QString FSTEProcess::setDataIntoExcel(QString exelFileName, QWidget *widget)
{
    QString dirPath = QCoreApplication::applicationDirPath()+"/"+InOutPath;

    QAxObject* excel = new QAxObject("Excel.Application", widget); //получаем указатьтель на excel
    //excel->dynamicCall( "SetVisible(bool)", true );
    QAxObject *workbooks = excel->querySubObject( "Workbooks" ); //получаем указатель на список книг
    QAxObject *workbook;
    if(QFile::exists(dirPath+"/"+exelFileName))
    {
        workbook  = workbooks->querySubObject( "Open(const QString&)", dirPath+"/"+exelFileName +".xls"); // открываем файл с диска с уже созданным документом Excel и получаем указатель на книгу
    }
    else
    {
        workbooks->dynamicCall("Add");
        workbook = excel->querySubObject("ActiveWorkBook");

    }
    int line = 1;
    QAxObject *range;
    QString valInc;
    QAxObject *razmer;

    //set header
    range = excel->querySubObject("Cells(Int, Int)", 1, 1);
    razmer = range->querySubObject("Columns");
    razmer->setProperty("ColumnWidth",30);
    range->dynamicCall( "SetValue(const QVariant&)", QVariant("Message Id"));

    range = excel->querySubObject("Cells(Int, Int)", 1, 2);
    razmer = range->querySubObject("Columns");
    razmer->setProperty("ColumnWidth",40);
    range->dynamicCall( "SetValue(const QVariant&)", QVariant("Message Current Text"));

    range = excel->querySubObject("Cells(Int, Int)", 1, 3);
    razmer = range->querySubObject("Columns");
    razmer->setProperty("ColumnWidth",40);
    range->dynamicCall( "SetValue(const QVariant&)", QVariant("New Message Text"));

    do
    {
         range = excel->querySubObject("Cells(Int, Int)", line, 1);
         valInc = range->dynamicCall("value").toString();
         line++;
    }
    while(valInc != "");
    line--;

    for(int i = 0;i<outList.size();i++)
    {
        range= excel->querySubObject("Cells(Int, Int)", line+i, 1);
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(outList[i].id));
        range= excel->querySubObject("Cells(Int, Int)", line+i, 2);
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(outList[i].srcMsg));
    }

    dirPath.replace("/","\\");
    //говорим excel что всякие служебные сообщения выводить не надо
    excel->setProperty("DisplayAlerts", 0);
    workbook->dynamicCall("SaveAs (const QString&)", dirPath+"\\"+exelFileName);
    workbook->dynamicCall("Close(Boolean)", false);
    excel->dynamicCall("Quit(void)");
    delete(excel);
    return "Data successfuly writen into excel file: "+exelFileName;
}

//проверяет, является ли полученная строка, строкой с  сообщением, и сохраняет
void FSTEProcess::convertMsgString(QString msgString)
{

    QRegExp hostMsgMask("^\\s{0,10}\\{\\s{0,20}(\\w{1,100})\\s{0,20}\,\\s\"([^\"]*)\"\\s\\}");
    QRegExp defaultMsgMask("[^\"]*\"([^\"]*)\"\\s{0,20}\,\\s{0,100}//\\s{0,20}(\\w{1,100})");

    if(hostMsgMask.indexIn(msgString)>=0)
    {
        if(hostMsgMask.cap(2).size() >= minMsgSize && hostMsgMask.cap(2).size()<= maxMsgSize)
        {
           addMessageToOutList(hostMsgMask.cap(1), hostMsgMask.cap(2));
        }
    }
    else if(defaultMsgMask.indexIn(msgString)>=0)
    {
        if(defaultMsgMask.cap(1).size()>= minMsgSize && defaultMsgMask.cap(1).size()<= maxMsgSize)
        {
            addMessageToOutList(defaultMsgMask.cap(2), defaultMsgMask.cap(1));
        }
    }
}

//проверяет строку с дефайном
int FSTEProcess::checkDefLine(QString inStr)
{
    int res = 0;
    int cur = 0;
    int bracketMarker = 0;
    bool notFlag = false;
    bool andFlag = false;

    QString sectorString;

    for(int i = 0; i < inStr.size(); i++)
    {
        if(inStr[i] == '(')
        {
            sectorString.clear();
            bracketMarker++;
        }
        else if(inStr[i] == ')')
        {
            bracketMarker--;

            if(bracketMarker == 0)
                cur = checkDef(sectorString);
            else
                cur = checkDefLine(sectorString);

            if(notFlag)
            {
                cur = 1 - cur;
                notFlag = false;
            }
            if(andFlag)
            {
                res*=cur;
                andFlag = false;
            }
            else
                res+=cur;
        }
        else if(inStr[i] == '!')
        {
            notFlag = true;
        }
        else if(inStr[i] == '&')
        {
            andFlag =  true;
        }
        else if (bracketMarker)
        {
            sectorString+=inStr[i];
        }
    }
    return res;

}

//проверяет строку и заполняет массив иерархии
void FSTEProcess::formHierarchy(QString inStr) //ierarhy corrected in this function
{
    bool last = tree.last();

    if(inStr.indexOf("#ifdef")>=0)
    {
        tree.push_back((last && checkDef(inStr))?true:false);
    }
    else if(inStr.indexOf("#ifndef")>=0)
    {
        tree.push_back((last && !checkDef(inStr))?true:false);
    }
    else if(inStr.indexOf("#if")>=0)
    {
        tree.push_back((last && checkDefLine(inStr))?true:false);
    }
    else if(inStr.indexOf("#else")>=0)
    {
        //invert status
       if(tree[tree.length()-2])
           last ? tree.last() = false : tree.last() = true;
    }
    else if(inStr.indexOf("#elif")>=0)
    {
        if(tree[tree.length()-2])
            checkDefLine(inStr) ? tree.last() = true : tree.last() = false;
    }
    else if(inStr.indexOf("#endif")>=0)
    {
        tree.pop_back();
    }

}

//проверяет, есть ли в полученой строке дефайн из списка дефайнов
int FSTEProcess::checkDef(QString inStr)
{
    int res = IGNORE_DEF;

    for(int i = 0; i < curDefsList.size(); i++)
    {
        if(inStr.indexOf(curDefsList.at(i))>=0)
        {
            res = INCLUDE_DEF;
            return res;
        }
    }
    return res;
}


FSTEProcess::~FSTEProcess()
{
    defsList.clear();
    outList.clear();
    tree.clear();
}

void FSTEProcess::processingSorceFile(QString fileName)
{
    QString curString;
    QFile srcFile(InOutPath+"/"+fileName);
    for(int i = 0; i<allDefsList.size(); i++)
    {
        curDefsList.clear();
        curDefsList = allDefsList[i].split(" ", QString::SkipEmptyParts);

        if(srcFile.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QRegExp defMask("(\\s|^)(#if|#else|#elif|#endif)");
            QRegExp notCommentMask("(^\\s|^)(//)");
            tree.clear();
            tree.push_back(true);

            while(!srcFile.atEnd())
            {
                curString.clear();
                curString = srcFile.readLine();

                if(notCommentMask.indexIn(curString)<0)
                {
                    if(defMask.indexIn(curString)>=0)
                    {
                        formHierarchy(curString);
                    }
                    else
                    {
                        if(tree.last() == 1)
                            convertMsgString(curString); //convert & write current string
                    }
                }
            }
            srcFile.close();
        }
    }
}

void FSTEProcess::addMessageToOutList(QString id, QString message)
{
    bool addFlag = true;

    for(int i = 0; i<outList.size(); i++)
    {
       if(outList.at(i).id == id && outList.at(i).srcMsg == message)
       {
           addFlag = false;
           break;
       }
    }

    if(addFlag)
    {
       outFSTE tmpObject;
       tmpObject.id = id;
       tmpObject.srcMsg = message;
       outList.push_back(tmpObject);
    }

}


void FSTEProcess::makeAllDefsList()
{
    QFile defineOrder("Config\\DefineOrder.txt");
    QStringList allDefs;
    QString tmpString;
    allDefsList.clear();
    if(defineOrder.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        tmpString = defineOrder.readLine();
        allDefs = tmpString.split("\t");
        defineOrder.close();
    }

    QFile defProcessOutput("ProcessOutput.txt");
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

            if(currentClientDefsList.at(0).indexOf(curDefsMask)>=0)
            {
              tmpDefsString.clear();
              for(int j = 1; j<currentClientDefsList.size(); j++)
              {
                  if(currentClientDefsList.at(j) == "+" && defsList.indexOf(allDefs.at(j-1))>=0)
                  {
                      tmpDefsString+=allDefs.at(j-1);
                      tmpDefsString+=" ";
                  }

              }

              allDefsList.push_back(tmpDefsString);
            }
        }
        defProcessOutput.close();
    }
    defsList.clear();
}
