#ifndef TCOMMONSERVER_H
#define TCOMMONSERVER_H

#include <QtGlobal>
#include <QHostAddress>
#include <QTime>

#include <thread>

#include "TCommonDefine.hpp"
#include "TConnectionServer.hpp"

using namespace connection ;

namespace server {

namespace commonDefineServer {

struct clientDescr ;
typedef std::shared_ptr <clientDescr> tdPtrClientDescr ;   ///< typedef для указателя на описание подключения клиента

                    /// Структура данных для одной итерации подбора
struct brutForceItem {
    tdPtrClientDescr ptrClientDesvt {nullptr} ;                     ///< Указатель на хост которому передан блок
    //        commonDefine::stateBruteForceItem bfState {commonDefine::bfUnknown};    ///< Состояние блока
    QString keyFound {""} ;                                                 ///< Найденный ключ
} ;
                    /// Описание подключения клиента
struct clientDescr {
    std::thread::id threadId ;                                ///< id потока. Является ключом в контейнере содержащим описание всех подключенных клиентов
    TConnection::state clientState {TConnection::stUnknown} ; ///< Состояние клиента/сервера. Например, для завершения работы очереди threadClient устанавливается состояние stAppClose
    //    QHostAddress clientAddress ;        ///< Хост с которым работает сервер. Возможно нужен будет для восстановления соединения при его потере
} ;
                    /// Описание структуры записи в лог
struct logItem {
    QTime itemTime {QTime::currentTime()} ; ///< Время события
    TConnection::exchangeProtocol command ; ///< Выполненная команда
    quint32 date ;                          ///< Данные передаваемые/получаемые
    QString comments ;                      ///< Комментарии
} ;

typedef std::shared_ptr <logItem> tdLogItem ;   ///< typedef для указателя на запись в лог

static std::mutex mutexConnectionList  ; // mutex для ожидания освобождения контейнера содержащего список соединений сервера
}
}
#endif // TCOMMONSERVER_H
