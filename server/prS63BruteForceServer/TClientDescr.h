#ifndef TCLIENTDESCR_H
#define TCLIENTDESCR_H

#include <QTcpSocket>

#include "TConnection.hpp"

namespace server {
//-------------------------------------------------------------------
/*!
 * \brief The TClientDescr class    Описание подключения клиента к серверу
 */
class TClientDescr : public connection::TConnection
{

private:
    QDateTime dateTime {QDateTime::currentDateTime()};        ///< Время выполнения последней операции
public:
    TClientDescr (QTcpSocket *);

    QDateTime getDateTime () { return dateTime ; } ///<

    bool operator () (const TClientDescr& inFirst, const TClientDescr& inSecond) ; ///< Оператор сравнения для контейнера Клиентов
};
}
#endif // TCLIENTDESCR_H
