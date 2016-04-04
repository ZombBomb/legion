#ifndef WIDGET_H
#define WIDGET_H
#include "fsteprocess.h"
#include "fetsprocess.h"
#include <QWidget>
#include <ActiveQt/QAxWidget>
#include <QDir>
#include <QProcess>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    public:
        explicit Widget(QWidget *parent = 0);
        ~Widget();

    private:
        Ui::Widget *ui;
        QStringList tmpFileList;
        bool checkFileListFiles();
        //void setGuiStatus(bool);
        QString getDefinesFromXls(QString softMaskStr);

        void updateDefines();
        QString convertFile(QString fileName);

    private slots:
        void fillSorceFile();
        void fillClientFile();
        void findDefines();
        void addSrcFile();
        void setExelFileName();
        void convertProcess();
};

#endif // WIDGET_H
