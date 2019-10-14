#ifndef TCONNECTION_HPP
#define TCONNECTION_HPP

#include <QObject>

namespace connection {

/*!
 * \brief The TConnection class Базовый класс для обслуживания работы распределенной системы
 */
class TConnection : public QObject
{
    Q_OBJECT
public:
    TConnection();
                                /// Протокол обмена между сервером и клиентами.
    enum exchangeProtocol {
                    /// Запрос клиента на подключение
        connectionRequest,
                    /// Подтверждение сервера о подключении и передача клиенту параметров работы. Запрос клиента о подключенности.
        connectionConfirm,
                    /// Завершение подключения
        connectionClose,
                    /// Со стороны сервере передается начальный ключ блока. Со стороны клиента передается подобранный ключ
        transferData,
                    /// Сервер и клиент подтверждают получение данных со стороны опонента
        acceptData,
                    /// Сервер и клиент отказываются от получение данных со стороны опонента.
        refuseData,
                    /// Запрос клиента нового блока
        transferRequest,
                    /// Запрос сервером или клиентом состояния опонента
        stateRequest,
                    /// Сервер или клиент возвращает свое состояние
        stateConfirm,
                    /// Количество команд в протоколе
        count} ;

    /// Возможные состояния
    enum state {
                    /// Состояние неопределено
        stUnknown,
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

public:
    state getState () ;            // Получение текущего состояния
    void setState (const state&) ; // Установка состояния

    bool virtual sendData (TConnection::exchangeProtocol, quint64) = 0 ;      // Виртуальный метод передачи данных
    bool virtual receiveData (TConnection::exchangeProtocol*, quint64*) = 0 ; // Виртуальный метод получения данных
};

}
#endif // TCONNECTION_HPP
