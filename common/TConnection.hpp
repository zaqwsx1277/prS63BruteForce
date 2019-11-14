#ifndef TCONNECTION_HPP
#define TCONNECTION_HPP

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

#include <memory>

namespace connection {

struct TDataTransfer ;

/*!
 * \brief The TConnection class Базовый класс для обслуживания работы распределенной системы
 */
class TConnection : public QObject
{
    Q_OBJECT
public:
    TConnection();
                                /// Протокол обмена между сервером и клиентами.
    enum exchangeProtocol  {
                    /// Команда не определена.
        cmdUnknown,
                    /// Запрос клиента на подключение
        cmdConnectionRequest,
                    /// Подтверждение сервера о подключении и передача клиенту параметров работы. Запрос клиента о подключенности.
        cmdConnectionConfirm,
                    /// Завершение подключения
        cmdConnectionClose,
                    /// Со стороны сервере передается начальный ключ блока. Со стороны клиента передается подобранный ключ
        cmdTransferData,
                    /// Сервер и клиент подтверждают получение данных со стороны опонента
        cmdAcceptData,
                    /// Сервер и клиент отказываются от получение данных со стороны опонента.
        cmdRefuseData,
                    /// Запрос клиента нового блока
        cmdTransferRequest,
                    /// Запрос сервером или клиентом состояния опонента
        cmdStateRequest,
                    /// Сервер или клиент возвращает свое состояние
        cmdStateConfirm,
                    /// Количество команд в протоколе
        cmdCount} ;

    /// Возможные состояния
    enum state {
                    /// Состояние неопределено
        stUnknown,
                    /// Соединение установлено
        stConnected,
                    /// Соединение разорванно
        stDisconnected,
                    /// Ожидание действий оператора
        stWait,
                    /// Готовность к запуску
        stReadyToStart,
                    /// Отсутствует готовность к запуску
        stNotReadyToStart,
                    /// Рабочий режим
        stStart,
                    /// Работа полностью остановлена
        stStop,
                    /// Произошла ошибка
        stError,
                    /// Поиск клиентом сервера
        stServerSearch,
                    /// Работа приостановлена
        stPause } ;

protected:

    state fState {stUnknown} ; // Текущее состояние
    std::shared_ptr <QTcpServer> fPtrServer {nullptr} ; // Указатель на сервер, который при работе будет постоянно прослушивать требуемый порт
    std::shared_ptr <QTcpSocket> fPtrSocket {nullptr} ; // Указатель на сокет, через который будет выполняться обмен данными с сервером

public:
    state getState () ;            // Получение текущего состояния
    void setState (const state&) ; // Установка состояния

    void sendData (const TConnection::exchangeProtocol, const quint64, std::shared_ptr <QTcpSocket> = nullptr) ;      // Метод передачи данных
    void sendData (const TDataTransfer&, std::shared_ptr <QTcpSocket> = nullptr) ;      // Метод передачи данных
    void receiveData (TDataTransfer&, const std::shared_ptr <QTcpSocket> = nullptr) ;   // Метод получения данных
};
//----------------------------------------------------------------------------------------------------------
/*!
 * \brief The TDataTransfer struct Формат передаваемых данных
 *
 *  Формат кадра передаваемых данных имеет фиксированный размер
 */
struct TDataTransfer
{
    quint32 title {0xFFFF} ;                // Заголовок передаваемых данных. Всегда должен быть равен 0хFFFF
    TConnection::exchangeProtocol command {TConnection::exchangeProtocol::cmdUnknown}; // Передаваемая команда
    qint64 data {0} ;                      // Передаваемые данные

    friend TDataTransfer& operator >> (QDataStream&, TDataTransfer&) ;
    friend QDataStream& operator << (QDataStream&, const TDataTransfer&) ;
};

}
#endif // TCONNECTION_HPP
