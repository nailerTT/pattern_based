#include "consolemessageshow.h"
#include "QDebug"
ConsoleMessageShow::ConsoleMessageShow(Subject *subject)
    :MessagePrint(subject)
{

}

void ConsoleMessageShow::PrintMsg(QString msg)
{
    qDebug() << msg;
}

void ConsoleMessageShow::PrintError(QString error)
{
    qDebug() << error;
}
