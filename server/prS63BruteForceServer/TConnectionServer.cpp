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
                                        // Прописываем все конекты необходимые для работы сервера. Он нужен только для обработки новых подключений и передачи QTcpSocket менеджеру новых подключений
    connect(fPtrServer.get(), &QTcpServer::newConnection, this, &TConnectionServer::slotNewHostConnected) ;
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
void TConnectionServer::slotNewHostConnected ()
{
    QTcpSocket* tcpSocked = fPtrServer -> nextPendingConnection() ;
    if (tcpSocked!= nullptr) {     // При подключении нового клиента кидаем сигнал серверу с его сокетом
        emit signalNewHostConnected (tcpSocked) ;
    }
}
//---------------------------------------------------
