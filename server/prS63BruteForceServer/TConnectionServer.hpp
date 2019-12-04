#ifndef TCONNECTIONSERVER_HPP
#define TCONNECTIONSERVER_HPP

#include "TConnection.hpp"

namespace connection {

//----------------------------------------------------------------
/*!
 * \brief The TConnectionServer class   Класс для работы с распределённой системой подбора ключей
 */
class TConnectionServer : public TConnection
{
public:
    TConnectionServer();

    void connectionClose () ;               // Закрываем соединение с клиентом

//private:
//    std::unique_ptr <QTcpServer> fPtrServer {new QTcpServer ()} ;   // Указатель на сервер обрабатывающий входящие подключения

//private slots:
//    void slotHostConnected () ;             // Слот срабатывающий при подключении клиента
//    void slotHostDisconnected () ;          // Слот срабатывающий при отключении клиента
//    void slotHostError(QAbstractSocket::SocketError) ; // Слот срабатывающий при ошибке при работе с клиентом
//    void slotHostReadyRead () ;             // Слот срабатывающий на сигнал готовности чтения данных

//signals:
//    void signalHostConnected (quint32) ;    // Сигнал передающий адрес подключенного клиента
//    void signalHostDisconnected (quint32) ; // Сигнал передающий адрес отключившегося клиента
//    void signalHostError(quint32, QAbstractSocket::SocketError); // Сигнал передающий код ошибки при работе с клиентом
};

}
#endif // TCONNECTIONSERVER_HPP
