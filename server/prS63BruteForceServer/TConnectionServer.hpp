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
        Q_OBJECT
public:
    TConnectionServer(const qint32&);
    ~TConnectionServer();

//    void connectionClose () ;               // Закрываем соединение с клиентом

private:


private slots:
    void slotHostNewConnected () ;               // Слот срабатывающий при нового подключении клиента
//    void slotHostDisconnected () ;          // Слот срабатывающий при отключении клиента
//    void slotHostError(QAbstractSocket::SocketError) ; // Слот срабатывающий при ошибке при работе с клиентом
//    void slotHostReadyRead () ;             // Слот срабатывающий на сигнал готовности чтения данных

signals:
    void signalHostNewConnected (QTcpSocket *) ; // Сигнал передающий сокет подключенного клиента
//    void signalHostDisconnected (quint32) ; // Сигнал передающий адрес отключившегося клиента
//    void signalHostError(quint32, QAbstractSocket::SocketError); // Сигнал передающий код ошибки при работе с клиентом
};

}
#endif // TCONNECTIONSERVER_HPP
