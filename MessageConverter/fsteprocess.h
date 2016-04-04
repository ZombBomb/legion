#ifndef FSTEPROCESS_H
#define FSTEPROCESS_H

#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <ActiveQt/QAxObject>
#include <QRegExp>
#include <QApplication>

struct outFSTE
{
    QString id;
    QString srcMsg;
};

class FSTEProcess
{
    public:
        QStringList defsList;
        QStringList curDefsList;
        QStringList allDefsList;
        QVector<outFSTE> outList;
        QString curDefsMask;
        int minMsgSize;
        int maxMsgSize;

        FSTEProcess();
        ~FSTEProcess();
        QString runFSTEProcess(QStringList curSrcFile, QWidget *widget);
        QString setDataIntoExcel(QString exelFileName, QWidget* widget);

    private:
        QVector<bool> tree;

        void makeAllDefsList();
        void convertMsgString(QString msgString);
        int checkDefLine(QString inStr);
        void formHierarchy(QString inStr);
        int checkDef(QString inStr);
        void processingSorceFile(QString fileName);
        void addMessageToOutList(QString id, QString message);
        void makeCurrentDefsList(QString);
};

#endif // PROCESS_H
