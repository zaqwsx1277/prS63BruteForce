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

private:

    QHostAddress fIpAddressServer = QHostAddress ()  ; // IP адрес сервера
    TConnectionClient::state fServerState {stUnknown} ; // Состояние сервера

    void makeSlotConnection (QTcpSocket*) ; // Для указанного Сокета создаются все нужные конекты

private slots:
    void slotHostConnected () ;     // Слот срабатывающий при нахождении сервера
    void slotHostDisconnected () ;  // Слот срабатывающий при отключении сервера
    void slotHostError (QAbstractSocket::SocketError) ; // Слот срабатывающий при ошибке обмена
    void slotHostReadyRead () ;     // Слот обрабатывающий получение данных от сервера

signals:                            // Все сигналы обрабатываются в основной форме
    void signalHostConnected (QHostAddress) ;   // Сигнал о подлючении к серверу.
    void signalHostDisconnected () ;            // Сигнал об отключении от сервера.
    void signalReadData (TDataTransfer) ;       // Сингал об успешном получении данных
};

}
#endif // TCONNECTIONCLIENT_HPP
