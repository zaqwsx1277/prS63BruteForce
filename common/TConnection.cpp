#include "TConnection.hpp"
#include "TException.hpp"

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
 * Обработка ошибок должна выполняться в наследуемом классе
 */
void TConnection::sendData (const TConnection::exchangeProtocol inCommand, const quint64 inSendData, std::shared_ptr <QTcpSocket> inSocket)
{
    QByteArray sendBlock ;
    QDataStream sendStream (&sendBlock, QIODevice::ReadWrite) ;

    sendStream << quint32 (0xFFFF) << inCommand << inSendData ;
    if (!inSocket)
        if (fPtrSocket)  fPtrSocket -> write(sendBlock) ;
          else throw exception::errConnectionSocket ;

      else inSocket -> write(sendBlock) ;
}
//-------------------------------------------------------------------
/*!
 * \brief connection::operator >>   Перегрузка потокового оператора получения данных
 * \param inStream
 * \param inData
 * \return
 */
TDataTransfer& connection::operator >> (QDataStream& inStream, TDataTransfer &inData)
{
    inStream >> inData.title ;
    int tempCommand ;
    inStream >> tempCommand ;
    inData.command =  static_cast <TConnection::exchangeProtocol> (tempCommand) ;
    inStream >> inData.data ;

    return inData ;
}
//-------------------------------------------------------------------
/*!
 * \brief connection::operator <<   Перегрузка потокового оператора передачи данных
 * \param inStream
 * \param inData
 * \return
 */
QDataStream& connection::operator << (QDataStream& inStream, const TDataTransfer&inData)
{
    inStream << inData.title << inData.command << inData.data ;
    return inStream ;
}
//-------------------------------------------------------------------
