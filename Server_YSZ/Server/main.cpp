#include "mainwindow.h"
#include <QApplication>
#include "QDebug"
#include "QTcpSocket"

#include "sqldatabase.h"
#include "lettersystem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
