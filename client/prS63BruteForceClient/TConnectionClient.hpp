#ifndef TCONNECTIONCLIENT_HPP
#define TCONNECTIONCLIENT_HPP

#include "TConnection.hpp"

#include <QHostAddress>
#include <QTcpSocket>

#include <memory>

namespace connection {
//----------------------------------------------------------------
/*!
 * \brief Класс для работы с сервером раздающим блоки ключей для подбора
 */
class TConnectionClient: public connection::TConnection
{
    Q_OBJECT
public:
    TConnectionClient();

    void seachServer (quint16) ;            // Поиск сервера в локальной сети
    QHostAddress getIpAddressServer () ;    // Получаем адрес найденного сервера

    bool sendData (TConnection::exchangeProtocol, quint64) { return true ;}      // Метод обработки передачи данных
    bool receiveData (TConnection::exchangeProtocol*, quint64*) { return true;}  // Метод обработки получения данных

private:

    QHostAddress fIpAddressServer = QHostAddress ()  ; // IP адрес сервера
    bool fIsServerExist {false} ;           // флаг нахождения сервера

    void makeSlotConnection (QTcpSocket*) ; // Для указанного Сокета создаются все нужные конекты

//    void xxx () ;
private slots:
    void slotHostConnected () ;     // Слот срабатывающий при нахождении сервера
    void slotHostDisconnected () ;  // Слот срабатывающий при отключении сервера
};

}
#endif // TCONNECTIONCLIENT_HPP
