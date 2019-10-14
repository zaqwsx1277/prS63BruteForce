#include "prServerEmulator.hpp"
#include "ui_prServerEmulator.h"


#include <QTcpSocket>
#include <QHostAddress>
//-----------------------------------------------------------------------------
prServerEmulator::prServerEmulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prServerEmulator)
{
    ui->setupUi(this);

    fPtrServer -> listen(QHostAddress::Any, 9993) ;

    connect (fPtrServer.get(), &QTcpServer::newConnection, this, &prServerEmulator::slotHostConnected) ;
    ui -> spClientAddress -> clear() ;
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
    QHostAddress xxx (fPtrServer -> nextPendingConnection() -> peerAddress ().toIPv4Address()) ;
    ui -> spClientAddress ->setText(xxx.toString()) ;
}
//-----------------------------------------------------------------------------

