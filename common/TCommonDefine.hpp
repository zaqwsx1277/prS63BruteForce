#ifndef TCOMMONDEFINE_H
#define TCOMMONDEFINE_H

#include <QHostAddress>

#include <memory>

namespace commonDefine {

    typedef std::shared_ptr <QHostAddress> tdHostAddress ; // typedef указателя на класс QHostAddress

    const quint16 portNumber {3333} ;   // Порт по умолчанию по которому выполняется передача данных
    const quint32 mainWindowRefresh {1000} ; // Время обновления основной формы
}
#endif // TCOMMONDEFINE_H
