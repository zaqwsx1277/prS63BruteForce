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

private:


private slots:
    void slotNewHostConnected () ;          // Слот срабатывающий при нового подключении клиента

signals:
    void signalNewHostConnected (QTcpSocket *) ; // Сигнал передающий сокет подключенного клиента
};

}
#endif // TCONNECTIONSERVER_HPP
