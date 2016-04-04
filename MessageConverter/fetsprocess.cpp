#include "fetsprocess.h"
const QString InOutPath = "InOutArea";
FETSProcess::FETSProcess()
{
    outList.clear();
}

FETSProcess::~FETSProcess()
{
    outList.clear();
}

//функция достает данные из excel файла и заполняет внутреннюю структуру объекта класса
QString FETSProcess::getDataFromExcel(QString exelFileName, QWidget* widget)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    outList.clear();
    QString dirPath = QCoreApplication::applicationDirPath()+"/"+InOutPath; //получаем путь к папке с приложением

    QAxObject* excel = new QAxObject("Excel.Application", widget); //получаем указатьтель на excel
    QAxObject *workbooks = excel->querySubObject( "Workbooks" ); //получаем указатель на список книг
    QAxObject *workbook = workbooks->querySubObject( "Open(const QString&)", dirPath+"/"+exelFileName ); // открываем файл с диска с уже созданным документом Excel и получаем указатель на книгу
    QAxObject *cell;

    outFETS tmpObj;

    int line = 2;
    do
    {
       tmpObj.clientMsg = "";
       tmpObj.id = "";
       cell = excel->querySubObject("Cells(Int, Int)", line, 1);
       tmpObj.id = cell->dynamicCall("value").toString();
       cell = excel->querySubObject("Cells(Int, Int)", line, 2);
       tmpObj.srcMsg = cell->dynamicCall("value").toString();
       cell = excel->querySubObject("Cells(Int, Int)", line, 3);
       tmpObj.clientMsg = cell->dynamicCall("value").toString();
       if(tmpObj.clientMsg!="")
       {
           outList.push_back(tmpObj);
       }
       line++;
    }
    while(tmpObj.id != "");

workbook->dynamicCall("Close(Boolean)", false);
excel->dynamicCall("Quit(void)");

delete(excel);
return "Excel file successfuly readed: "+exelFileName;
}

//функция заменяет в файле строки сообщений на новые
QString FETSProcess::setDataIntoSrc(QString srcFileName)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    QString curString;
    QString filePath = InOutPath+"/"+srcFileName;
    QFile srcFile(filePath);
    QStringList listOfData;
    listOfData.clear();
    QRegExp notCommentMask("(^\\s|^)(//)");
    QRegExp regId("");


    if(!srcFile.open(QIODevice::ReadOnly|QIODevice::Text))return "Can`t open for read sorce file: "+srcFileName;

    while(!srcFile.atEnd())
    {
        curString.clear();
        curString = srcFile.readLine();


        for(int i = 0; i<outList.size(); i++)
        {
            regId.setPattern("\\b"+outList[i].id+"\\b");
            //проверка что строка подходящая, что строка не закомментирована, что сообщение клиента не пустое
            if(regId.indexIn(curString)>=0 &&
                    curString.indexOf("\""+outList[i].srcMsg+"\"")>=0 &&
                    outList[i].clientMsg!="" &&
                    notCommentMask.indexIn(curString)<0)
            {
                curString.replace("\""+outList[i].srcMsg+"\"","\""+outList[i].clientMsg+"\"");
                outList.remove(i);
                break;
            }
        }
        listOfData.push_back(curString);
    }

    srcFile.close();
    if(!srcFile.open(QIODevice::WriteOnly|QIODevice::Text))return "Can`t open for write sorce file: "+srcFileName;
    QTextStream stream(&srcFile);
    stream.setCodec("Windows-1252");
    for(int j = 0; j < listOfData.size(); j++)
        stream<<listOfData.at(j);
    stream.flush();
    srcFile.close();
    return "Sorce file successfuly corrected: "+srcFileName;
}
