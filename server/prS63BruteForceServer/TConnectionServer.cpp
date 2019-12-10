#include "TConnectionServer.hpp"

using namespace connection ;
//---------------------------------------------------
/*!
 * \brief connection::TConnectionServer::TConnectionServer  Конструктор
 */
TConnectionServer::TConnectionServer(const qint32& inPortNumber) : TConnection ()
{

}
//---------------------------------------------------
/*!
 * \brief TConnectionServer::slotHostConnected Слот срабатывающий при нового подключении клиента
 */
//void TConnectionServer::slotHostConnected ()
//{
//    QTcpSocket* tcpSocked = fPtrServer -> nextPendingConnection() ;
//    if (tcpSocked!= nullptr) {     // При подключении нового клиента формируем все необходимые коннекты и кидаем сигнал серверу
//        emit signalHostConnected (tcpSocked) ;
//    }
//}
//---------------------------------------------------
