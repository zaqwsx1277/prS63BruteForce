#ifndef TCOMMONDEFINE_H
#define TCOMMONDEFINE_H

#include <QHostAddress>

#include <memory>

namespace commonDefine {

    typedef std::shared_ptr <QHostAddress> tdHostAddress ; // typedef указателя на класс QHostAddress

    const quint16 portNumber {3333} ;   // Порт по умолчанию по которому выполняется передача данных
}
#endif // TCOMMONDEFINE_H
