#include "TSEConnection.hpp"

#include <QTcpSocket>
#include <QHostAddress>

using namespace connection ;
//----------------------------------------------------------------------------------
TSEConnection::TSEConnection() : TConnection ()
{
    fPtrServer -> listen(QHostAddress::Any, 9993) ;

    connect (fPtrServer.get(), &QTcpServer::newConnection, this, &TSEConnection::slotHostConnected) ;
}
//----------------------------------------------------------------------------------
/*!
 * \brief TSEConnection::slotHostConnected  Слот срабатывающий при подключении клиента
 */
void TSEConnection::slotHostConnected ()
{
    emit signalHostConnected (fPtrServer -> nextPendingConnection() -> peerAddress ().toIPv4Address()) ;
}
//-----------------------------------------------------------------------------------
