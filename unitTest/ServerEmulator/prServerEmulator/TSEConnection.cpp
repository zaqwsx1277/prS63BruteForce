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
    fPtrSocket  = fPtrServer -> nextPendingConnection() ;
    if (fPtrSocket != nullptr) {
        connect (fPtrSocket, &QTcpSocket::disconnected, this, &TSEConnection::slotHostDisconnected) ;
        connect (fPtrSocket, SIGNAL (error (QAbstractSocket::SocketError)), this, SLOT (slotHostError (QAbstractSocket::SocketError))) ;
        connect (fPtrSocket, &QTcpSocket::readyRead, this, &TSEConnection::slotHostReadyRead) ;

        emit signalHostConnected (fPtrSocket  -> peerAddress ().toIPv4Address()) ;
    }
}
//-----------------------------------------------------------------------------------
/*!
 * \brief slotHostDisconnected  Слот срабатывающий при отключении клиента
 */
void TSEConnection::slotHostDisconnected ()
{
    QTcpSocket* ptrSocket = qobject_cast <QTcpSocket*> (sender ()) ;
    if (ptrSocket != nullptr) {
        emit signalHostDisconnected(ptrSocket ->peerAddress().toIPv4Address());
    }
}
//-----------------------------------------------------------------------------------
/*!
 * \brief slotHostDisconnected  Слот срабатывающий при ошибке при работе с клиентом
 */
void TSEConnection::slotHostError(QAbstractSocket::SocketError inError)
{
    QTcpSocket* ptrSocket = qobject_cast <QTcpSocket*> (sender ()) ;
    if (ptrSocket != nullptr) {
        emit signalHostError(ptrSocket ->peerAddress().toIPv4Address(), inError);
    }
}
//-----------------------------------------------------------------------------------
/*!
 * \brief TSEConnection::slotHostReadyRead  Слот срабатывающий на сигнал готовности чтения данных
 */
void TSEConnection::slotHostReadyRead ()
{

}
//-----------------------------------------------------------------------------------
/*!
 * \brief TSEConnection::connectionClose
 */
void TSEConnection::connectionClose ()
{
    fPtrSocket  -> disconnectFromHost() ;
}
//-----------------------------------------------------------------------------------
