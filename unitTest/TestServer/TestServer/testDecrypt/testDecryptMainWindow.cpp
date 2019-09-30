#include "testDecryptMainWindow.hpp"
#include "ui_testdecryptmainwindow.h"

testDecryptMainWindow::testDecryptMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testDecryptMainWindow)
{
    ui->setupUi(this);
}

testDecryptMainWindow::~testDecryptMainWindow()
{
    delete ui;
}
