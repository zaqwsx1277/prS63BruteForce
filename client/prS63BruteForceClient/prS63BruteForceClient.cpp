#include "prS63BruteForceClient.hpp"
#include "ui_prS63BruteForceClient.h"

prS63BruteForceClient::prS63BruteForceClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceClient)
{
    ui->setupUi(this);
}

prS63BruteForceClient::~prS63BruteForceClient()
{
    delete ui;
}
