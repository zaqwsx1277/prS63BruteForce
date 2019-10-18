#include "TConnection.hpp"

using namespace connection ;

//-------------------------------------------------------------------
/*!
 * \brief TConnection::TConnection  Конструктор класса
 */
TConnection::TConnection()
{

}
//-------------------------------------------------------------------
/*!
 * \brief TConnection::getState Получение состояния соединения
 * \return Состояние соединения
 */
TConnection::state connection::TConnection::getState ()
{
    return fState ;
}
//-------------------------------------------------------------------
/*!
 * \brief TConnection::setState Установка состояния соединения
 * \param inState   Устанавливаемое соединение
 */
void TConnection::setState (const TConnection::state& inState)
{
    fState = inState ;
}
//-------------------------------------------------------------------
/*!
 * \brief TConnection::sendData Метод передачи данных
 * \param inCommand     Команда (enum exchangeProtocol)
 * \param inSendData    Передаваемые данные. Как правило это quint64 (8 байт)
 * \param inSocket      Сокет через который выполняется передача. По умолчание передача выполняется через fPtrSocket
 *
 * При ошибках кидается exeption
 */
void TConnection::sendData (TConnection::exchangeProtocol inCommand, quint64 inSendData, std::unique_ptr <QTcpSocket> inSocket)
{

}
//-------------------------------------------------------------------
