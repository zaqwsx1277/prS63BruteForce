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
    QTime timeReceiveBlock ;    // Время получения начального значения ключа
    quint64 keyFirst {0} ;      // Первый ключ в блоке
    std::array <quint64, maxThreads> keys {0} ; // обрабатываемые ключи
    QTime timeSendResult ;      // Время передачи результата
    QString result {""} ;       // 0 - если подобранных ключей нет, или список подобранных ключей разделённых запятой
};

typedef std::shared_ptr <QHostAddress> tdHostAddress ;      // typedef указателя на класс QHostAddress
typedef std::shared_ptr <TLogItemClient> tdLogItemClient ;  // typedef указателя на структуру TLogItemClient

const QString HeaderTimeReceiveBlock = "Время получения ключа" ;    // Заголовки таблицы ведения лога
const QString HeaderKeyFirst = "Начальный ключ" ;
const QString HeaderTimeSendResult = "Время отправки результата" ;
const QString HeaderResult = "Результат" ;

}
#endif // TCOMMONDEFANECLIENT_H
