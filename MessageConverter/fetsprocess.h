#ifndef FETSPROCESS_H
#define FETSPROCESS_H

#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <ActiveQt/QAxObject>
#include <QRegExp>
#include <QApplication>
#include <QTextCodec>
struct outFETS
{
    QString id;
    QString srcMsg;
    QString clientMsg;
};
class FETSProcess
{
    public:
        FETSProcess();
        ~FETSProcess();

        QString getDataFromExcel(QString exelFileName, QWidget* widget);
        QString setDataIntoSrc(QString srcFileName);

    private:
        QVector<outFETS> outList;


};

#endif // FETSPROCESS_H
