#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpServer>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTcpServer *m_ptcpServer = new QTcpServer(this);
    m_ptcpServer->listen(QHostAddress::Any, 3333) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
