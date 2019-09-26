#include "TConnection.hpp"

//-------------------------------------------------------------------
/*!
 * \brief TConnection::TConnection  Конструктор класса
 */
connection::TConnection::TConnection()
{

}
//-------------------------------------------------------------------
/*!
 * \brief TConnection::getState Получение состояния соединения
 * \return Состояние соединения
 */
connection::TConnection::state connection::TConnection::getState ()
{
    return fState ;
}
//-------------------------------------------------------------------
/*!
 * \brief TConnection::setState Установка состояния соединения
 * \param inState   Устанавливаемое соединение
 */
void connection::TConnection::setState (const connection::TConnection::state& inState)
{
    fState = inState ;
}
//-------------------------------------------------------------------
