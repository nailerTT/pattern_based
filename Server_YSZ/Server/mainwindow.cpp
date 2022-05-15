#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "texteditprinter.h"
#include <QTextBrowser>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,_listener(nullptr)
{
    ui->setupUi(this);
    start = false;
    QTextBrowser* output = this->findChild<QTextBrowser*>("output");
    _listener = new NetWorkLisener(10,new TextEditPrinter(nullptr,output));
    QPushButton* btn = this->findChild<QPushButton*>("btn");
    btn->setText("start");
    connect(_listener,&NetWorkLisener::NewMsg,this,&MainWindow::newRequest);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _listener;
    _listener = nullptr;
}

void MainWindow::newRequest(QString msg)
{
    QString res = execute.execute(msg);
    QTextBrowser* output = this->findChild<QTextBrowser*>("output");
    output->append(res);
}


void MainWindow::on_btn_clicked()
{
    if(start)
    {
        _listener->CloseServer();
        QPushButton* btn = this->findChild<QPushButton*>("btn");
        btn->setText("start");
        start = false;
    }
    else{
        _listener->InitServer();
        QPushButton* btn = this->findChild<QPushButton*>("btn");
        btn->setText("stop");
        start = true;
    }
}

