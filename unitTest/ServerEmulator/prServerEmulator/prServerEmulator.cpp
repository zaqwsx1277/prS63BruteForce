#include "prServerEmulator.hpp"
#include "ui_prServerEmulator.h"

//-----------------------------------------------------------------------------
prServerEmulator::prServerEmulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prServerEmulator)
{
    ui->setupUi(this);

    fPtrServer -> listen(QHostAddress::Any, 9993) ;

    connect (fPtrServer.get(), &QTcpServer::newConnection, this, &prServerEmulator::slotHostConnected) ;
}
//------------------------------------------------------------------------------
prServerEmulator::~prServerEmulator()
{
    delete ui;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prServerEmulator::slotHostConnected  Слот срабатывающий при подключении клиента
 */
void prServerEmulator::slotHostConnected ()
{
    int i = 0 ;
}
//-----------------------------------------------------------------------------

void prServerEmulator::on_pushButton_clicked()
{
    fPtrServer -> close();
    this -> close() ;
}
//-----------------------------------------------------------------------------
