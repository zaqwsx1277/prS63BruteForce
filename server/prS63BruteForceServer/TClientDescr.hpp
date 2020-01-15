#ifndef TCLIENTDESCR_H
#define TCLIENTDESCR_H

#include <QTcpSocket>
#include <QDateTime>

#include "TConnection.hpp"
#include "TClientDescr.hpp"

namespace server {
//-------------------------------------------------------------------
/*!
 * \brief The TClientDescr class    Описание подключения клиента к серверу
 */
class TClientDescr : public connection::TConnection
{

private:
    QDateTime dateTime {QDateTime::currentDateTime()};      ///< Время выполнения последней операции. Она нужна для обработки
public:
    TClientDescr (QTcpSocket *);

    QDateTime getDateTime () { return dateTime ; }          ///< Получение даты и времени выполнения последней операции

    bool operator () (const TClientDescr& inFirst, const TClientDescr& inSecond) ; ///< Оператор сравнения для контейнера Клиентов
};
}
#endif // TCLIENTDESCR_H
