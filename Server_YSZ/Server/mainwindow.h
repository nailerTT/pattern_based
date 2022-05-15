#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networklisener.h"
#include "QString"
#include "iexecute.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void newRequest(QString msg);
private slots:
    void on_btn_clicked();

private:
    Ui::MainWindow *ui;
    bool start;
    NetWorkLisener* _listener;
    Execute execute;
};
#endif // MAINWINDOW_H
