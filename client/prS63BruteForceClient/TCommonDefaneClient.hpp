#ifndef TCOMMONDEFANECLIENT_H
#define TCOMMONDEFANECLIENT_H

#include <QTime>
#include <QHostAddress>

#include <array>
#include <memory>

namespace commonDefineClient {

#define maxThreads 256      // Максимальное количество потоков. Нужно для обеспечения максимальной производительности подбора и поэтому с модели используется std::array

struct TLogItemClient       // Структура данных выводимых в лог
{
    QTime timeReceiveBlock = QTime::currentTime() ; // Время получения начального значения ключа
    quint64 keyFirst {0} ;      // Первый ключ в блоке
    std::array <quint64, maxThreads> keys {0} ; // обрабатываемые ключи
    QTime timeSendResult ;      // Время передачи результата
    QString result {""} ;       // 0 - если подобранных ключей нет, или список подобранных ключей разделённых запятой
    QString comment {""} ;      // Комментарий
};

typedef std::shared_ptr <QHostAddress> tdHostAddress ;      // typedef указателя на класс QHostAddress
typedef std::shared_ptr <TLogItemClient> tdLogItemClient ;  // typedef указателя на структуру TLogItemClient

const QString HeaderTimeReceiveBlock {"Время\nполучения\nключа"} ;    // Заголовки таблицы ведения лога
const QString HeaderKeyFirst {"Начальный\nключ"} ;
const QString HeaderTimeSendResult {"Время\nотправки\nрезультата"} ;
const QString HeaderResult {"Результат"} ;
const QString HeaderComment {"Комментарий"} ;

const QString stateUnknown {"Неопределено"} ;               // Описание возможных состояний
const QString stateError {"Ошибка"} ;
const QString stateWait {"Ожидание действий оператора"} ;
const QString stateStart {"Выполнение основного цикла подбора"} ;
const QString stateStop {"Процесс подбора остановлен"} ;
const QString stateServerSearch {"Выполняется автоматический поиск сервера"} ;
const QString statePause {"Выполнение подбора приостановлено"} ;
const QString stateConnectedToServer {"Подключен к серверу"} ;
const QString stateDisconnectedFromServer {"Отключен от сервера"} ;

const QString logServerConnected {"Клиент подключен к серверу: "} ;     // Описание возможных записей в лог
const QString logServerDisconnected {"Клиент отключен от сервера: "} ;
const QString logServerStateRequest {"Получен запрос состояния от сервера: "} ;

const quint32 timerRefresh {1000} ;                         // значение таймера для обновления формы

}
#endif // TCOMMONDEFANECLIENT_H
