#ifndef TCOMMONSERVER_H
#define TCOMMONSERVER_H

#include <QtGlobal>
#include <QHostAddress>

#include "TCommonDefine.hpp"

namespace server {

namespace commonDefineServer {

        /// Структура данных для одной итерации подбора
    struct brutForceItem {
        commonDefine::tdHostAddress hostAddress {nullptr} ; // Указатель на хост которому передан блок
        commonDefine::stateBruteForceItem bfState {commonDefine::bfUnknown}; // Состояние блока
        QString keyFound {""} ;                             // Найденный ключ
    } ;
}
}
#endif // TCOMMONSERVER_H
