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

    bool sendData (TConnection::exchangeProtocol, quint64) { ; }
    bool receiveData (TConnection::exchangeProtocol*, quint64*) { ; }
};

}
#endif // TCONNECTIONSERVER_HPP
