#include "TConnectionServer.hpp"

#include "TException.hpp"

using namespace connection ;
//---------------------------------------------------
/*!
 * \brief connection::TConnectionServer::TConnectionServer  Конструктор
 */
TConnectionServer::TConnectionServer(const qint32& inPortNumber) : TConnection ()
{
    fPtrServer = std::make_unique <QTcpServer> () ;
    if (!fPtrServer -> listen(QHostAddress::Any, inPortNumber)) throw exception::errServerStart ;
                                        // Прописываем все конекты необходимые для работы сервера
    connect(fPtrServer.get(), &QTcpServer::newConnection, this, &TConnectionServer::slotHostNewConnected) ;
}
//---------------------------------------------------
/*!
 * \brief TConnectionServer::~TConnectionServer Деструктор
 */
TConnectionServer::~TConnectionServer()
{
    fPtrServer.reset();
}
//---------------------------------------------------
/*!
 * \brief TConnectionServer::slotHostConnected Слот срабатывающий при нового подключении клиента
 */
void TConnectionServer::slotHostNewConnected ()
{
//    QTcpSocket* tcpSocked = fPtrServer -> nextPendingConnection() ;
//    if (tcpSocked!= nullptr) {     // При подключении нового клиента формируем все необходимые коннекты и кидаем сигнал серверу
//        emit signalHostConnected (tcpSocked) ;
//    }
}
//---------------------------------------------------
