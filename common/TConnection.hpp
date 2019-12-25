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
    ~TConnection();
                                /// Протокол обмена между сервером и клиентами.
    enum exchangeProtocol  {
        cmdUnknown = 0,         ///< Команда не определена.
        cmdConnectionRequest,   ///< Запрос клиента на подключение
        cmdConnectionConfirm,   ///< Подтверждение сервера о подключении и передача клиенту параметров работы.
        cmdConnectionReject,    ///< Сервер отказывется от подключения клиента ((условия такого отказа пока неопределены).
        cmdConnectionClose,     ///< Завершение подключения
        cmdTransferData,        ///< Со стороны сервере передается начальный ключ блока. Со стороны клиента передается подобранный ключ
        cmdAcceptData,          ///< Сервер и клиент подтверждают получение данных со стороны опонента
        cmdRefuseData,          ///< Сервер и клиент отказываются от получение данных со стороны опонента.
        cmdTransferRequest,     ///< Запрос клиентом нового блока
        cmdStateRequest,        ///< Запрос сервером или клиентом состояния опонента
        cmdStateConfirm,        ///< Сервер или клиент возвращает свое состояние
        cmdError,               ///< Сообщение об ошибке (необходимо для ведения лога)
        cmdCount                ///< Количество команд в протоколе
    } ;

    /// Возможные состояния
    enum state {
        stUnknown = 0,          ///< Состояние неопределено
        stConnected,            ///< Соединение установлено
        stDisconnected,         ///< Соединение разорванно
        stWait,                 ///< Ожидание действий оператора
        stReadyToStart,         ///< Готовность к запуску
        stNotReadyToStart,      ///< Отсутствует готовность к запуску
        stStart,                ///< Рабочий режим
        stStop,                 ///< Работа полностью остановлена
        stError,                ///< Произошла ошибка
        stServerSearch,         ///< Поиск клиентом сервера
        stPause,                ///< Работа приостановлена
        stAppClose,             ///< Завершение работы приложения
        stCount
    } ;

protected:
    state fState {stUnknown} ; // Текущее состояние

public:
    std::unique_ptr <QTcpServer> fPtrServer {nullptr} ; // Указатель на сервер, который при работе будет постоянно прослушивать требуемый порт
    std::shared_ptr <QTcpSocket> fPtrSocket {nullptr} ; // Указатель на сокет, через который будет выполняться обмен данными с сервером

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
    quint32 title {0xFFFF} ;                ///< Заголовок передаваемых данных. Всегда должен быть равен 0хFFFF
    TConnection::exchangeProtocol command {TConnection::exchangeProtocol::cmdUnknown}; ///< Передаваемая команда
    qint64 data {0} ;                      ///< Передаваемые данные

    friend TDataTransfer& operator >> (QDataStream&, TDataTransfer&) ;
    friend QDataStream& operator << (QDataStream&, const TDataTransfer&) ;
};

}
#endif // TCONNECTION_HPP
