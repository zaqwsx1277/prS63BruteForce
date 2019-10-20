#ifndef TSEMULATORDEFINE_H
#define TSEMULATORDEFINE_H

#include <QTime>

#include <memory>

namespace seDefine {

struct TLogItem {
    QTime itemTime {QTime::currentTime()} ; // Время события
    quint32 itemCommand ;                   // Выполненная команда
    QString comments ;                      // Комментрарии
} ;

typedef std::shared_ptr <TLogItem> tdLogItem ;  // typedef указателя на структуру TLogItemClient

}
#endif // TSEMULATORDEFINE_H
