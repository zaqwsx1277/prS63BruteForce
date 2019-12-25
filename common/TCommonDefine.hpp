#ifndef TCOMMONDEFINE_H
#define TCOMMONDEFINE_H

#include <QHostAddress>
#include <QString>

#include <memory>
#include <mutex>

#include "TConnection.hpp"

namespace commonDefine {

    typedef std::shared_ptr <QHostAddress> tdHostAddress ; ///< typedef указателя на класс QHostAddress

    const quint16 portNumber {9993} ;           ///< Порт по умолчанию по которому выполняется передача данных
    const quint32 stateRefresh {5000} ;         ///< Время запроса состояния клиента/сервера

    static std::mutex mutexRefresh ;            ///< mutex для ожидания записи в модель отображения лога

    static const QString fileSettingsName {"prBruteForce.ini"} ; ///< Имя файла с настройками проекта
                                                // Наименования секций в файле настроек
    static const QString setSrvFileName {"server/fileNameS63"} ;
    static const QString setSrvKeyStart {"server/keyStart"} ;
    static const QString setSrvKeyStop {"server/keyStop"} ;
    static const QString setSrvFileNameLog {"server/fileNameLog"} ;

    //----------------------------------------------------------------------------------------------------------
    static std::vector <QString> exchangeProtocolText {     ///< Текстовое описание команд протокола обмена
        "Команда не определена",
        "Запрос клиента на подключение",
        "Подтверждение о подключении",
        "Отказ от подключения",
        "Закрытие подключения",
        "Передача данных",
        "Подтверждение получения данных",
        "Отказ от получения данных",
        "Запрос данных",
        "Запрос состояния",
        "Возврат состояния",
        "Сообщение об ошибке"
    } ;

    static std::vector <QString> stateText {                ///< Текстовое описание возможный состояний
        "Неопределено",
        "Соединение установлено",
        "Соединение разорванно",
        "Ожидание действий оператора",
        "Готовность к запуску",
        "Отсутствует готовность к запуску",
        "Рабочий режим",
        "Работа полностью остановлена",
        "Произошла ошибка",
        "Поиск сервера",
        "Работа приостановлена",
        "Завершение работы приложени"
    } ;
}

#endif // TCOMMONDEFINE_H
