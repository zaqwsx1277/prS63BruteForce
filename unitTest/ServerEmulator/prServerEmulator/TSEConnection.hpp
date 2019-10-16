#ifndef TSECONNECTION_HPP
#define TSECONNECTION_HPP

#include <memory>

#include <QTcpServer>

#include "TConnection.hpp"

namespace connection {

class TSEConnection : public TConnection
{
    Q_OBJECT

public:
    TSEConnection();
    bool sendData (TConnection::exchangeProtocol, quint64) { return true ; }
    bool receiveData (TConnection::exchangeProtocol*, quint64*) {return true ;}

    void connectionClose () ;               // Закрываем соединение с клиентом

private:
    std::unique_ptr <QTcpServer> fPtrServer {new QTcpServer ()} ;   // Указатель на сервер обрабатывающий входящие подключения
    QTcpSocket *fPtrSocket {nullptr} ;      // Указатель на сокет обрабатывающий обмен данными с клиентом

private slots:
    void slotHostConnected () ;             // Слот срабатывающий при подключении клиента
    void slotHostDisconnected () ;          // Слот срабатывающий при отключении клиента
    void slotHostError(QAbstractSocket::SocketError) ; // Слот срабатывающий при ошибке при работе с клиентом
    void slotHostReadyRead () ;             // Слот срабатывающий на сигнал готовности чтения данных

signals:
    void signalHostConnected (quint32) ;    // Сигнал передающий адрес подключенного клиента
    void signalHostDisconnected (quint32) ; // Сигнал передающий адрес отключившегося клиента
    void signalHostError(quint32, QAbstractSocket::SocketError); // Сигнал передающий код ошибки при работе с клиентом
};

}
#endif // TSECONNECTION_HPP
