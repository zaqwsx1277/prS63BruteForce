#include "TConnectionServer.hpp"

using namespace connection ;
//---------------------------------------------------
/*!
 * \brief connection::TConnectionServer::TConnectionServer  Конструктор
 */
TConnectionServer::TConnectionServer() : TConnection ()
{

}
//---------------------------------------------------
/*!
 * \brief TConnectionServer::slotHostConnected Слот срабатывающий при нового подключении клиента
 */
void TConnectionServer::slotHostConnected ()
{
    if (fPtrServer -> nextPendingConnection() != nullptr) {     // При подключении нового клиента формируем все необходимые коннекты и кидаем сигнал серверу
//        connect (fPtrSocket.get(), &QTcpSocket::disconnected, this, &TSEConnection::slotHostDisconnected) ;
//        connect (fPtrSocket.get(), SIGNAL (error (QAbstractSocket::SocketError)), this, SLOT (slotHostError (QAbstractSocket::SocketError))) ;
//        connect (fPtrSocket.get(), &QTcpSocket::readyRead, this, &TSEConnection::slotHostReadyRead) ;

        signalHostConnected (fPtrServer -> nextPendingConnection()) ;
//        emit signalHostConnected () ;
    }
}
//---------------------------------------------------
