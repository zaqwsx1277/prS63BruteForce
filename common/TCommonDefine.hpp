#ifndef TCOMMONDEFINE_H
#define TCOMMONDEFINE_H

#include <QHostAddress>

#include <memory>

namespace commonDefine {

    typedef std::shared_ptr <QHostAddress> tdHostAddress ; // typedef указателя на класс QHostAddress

    enum stateBruteForceItem {bfUnknown = 0, bfStart, bfFind, fsEmpty, bfStop, bfPause } ; // Состояния при выполнении подбора

    const quint16 portNumber {9993} ;   /// Порт по умолчанию по которому выполняется передача данных
    const quint32 mainWindowRefresh {1000} ; /// Время обновления основной формы
}
#endif // TCOMMONDEFINE_H
