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

private:
    std::unique_ptr <QTcpServer> fPtrServer {new QTcpServer ()} ;   // Указатель на сервер обрабатывающий входящие подключения

private slots:
    void slotHostConnected () ;             // Слот срабатывающий при подключении клиента

signals:
    void signalHostConnected (quint32) ;    // Сигнал передающий адрес подключенного клиента
};

}
#endif // TSECONNECTION_HPP
