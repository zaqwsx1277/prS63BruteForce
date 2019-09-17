#ifndef TCOMMONDEFINE_H
#define TCOMMONDEFINE_H

#include <QHostAddress>

#include <memory>

namespace commonDefine {

    typedef std::shared_ptr <QHostAddress> tdHostAddress ; // typedef указателя на класс QHostAddress

    const quint32 portNumber {9939} ;   // Порт по умолчанию по которому выполняется передача данных
}
#endif // TCOMMONDEFINE_H
