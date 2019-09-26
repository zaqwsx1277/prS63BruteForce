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
    enum exchangeProtocol {connectionRequest,   /// Запрос клиента на подключение
                           connectionConfirm,   /// Подтверждение сервера о подключении. Запрос клиента о подключенности
                           connectionClose,     /// Завершение подключения
                           transferData,        /// Со стороны сервере передается начальный ключ. Со стороны клиента передается подобранный ключ
                           transferRequest,     /// Запрос клиента нового блока
                           stateRequest,        /// Запрос сервером или клиентом состояния опонента
                           stateConfirm,        /// Сервер или клиент возвращает свое состояние
                           count} ;             /// Количество команд в протоколе
    /// Возможные состояния
    enum state {stUnknown,
                stWait,         /// Ожидание действий оператора
                stReadyToStart, /// Готовность к запуску
                stNotReadyToStart, /// Отсутствует готовность к запуску
                stStart,        /// Рабочий режим
                stStop,         /// Работа полностью остановлена
                stError,        /// Произошла ошибка
                stServerSearch, /// Поиск клиентом сервера
                stPause } ;     /// Работа приостановлена

protected:

    TConnection::state fState {stUnknown} ; // Текущее состояние

public:
    TConnection::state getState () ;            // Получение текущего состояния
    void setState (TConnection::state&) ;        // Установка состояния

    bool virtual sendData (TConnection::exchangeProtocol, quint64) = 0 ;      // Виртуальный метод передачи данных
    bool virtual receiveData (TConnection::exchangeProtocol*, quint64*) = 0 ; // Виртуальный метод получения данных
};

}
#endif // TCONNECTION_HPP
