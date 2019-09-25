#ifndef TCOMMONSERVER_H
#define TCOMMONSERVER_H

#include <QtGlobal>
#include <QHostAddress>

#include "TCommonDefine.hpp"

namespace commonDefineServer {
            /// Структура данных для одной итерации подбора
    struct brutForceItem {
        commonDefine::tdHostAddress hostAddress {nullptr} ; // Указатель на ност которому передан блок
//        state ; // Состояние блока
        QString keyFound {""} ;                             // Найденный ключ
    }
}

#endif // TCOMMONSERVER_H
