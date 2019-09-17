#ifndef TCONNECTIONCLIENT_HPP
#define TCONNECTIONCLIENT_HPP

#include "TConnection.hpp"

class TConnectionClient: public TConnection
{
public:
    TConnectionClient();

private:
    void seachServer () ;       // Поиск сервера в локальной сети

private slots:
    void slotHostConnected () ; // Слот срабатывающий при нахождении сервера
};

#endif // TCONNECTIONCLIENT_HPP
