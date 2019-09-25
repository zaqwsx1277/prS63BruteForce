#include "prS63BruteForceServer.hpp"
#include "ui_prS63BruteForceServer.h"

prS63BruteForceServer::prS63BruteForceServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceServer)
{
    ui->setupUi(this);
}

prS63BruteForceServer::~prS63BruteForceServer()
{
    delete ui;
}
