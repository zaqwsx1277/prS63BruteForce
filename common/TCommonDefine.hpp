#ifndef TCOMMONDEFINE_H
#define TCOMMONDEFINE_H

#include <QHostAddress>
#include <QString>

#include <memory>
#include <mutex>

namespace commonDefine {

    typedef std::shared_ptr <QHostAddress> tdHostAddress ; ///< typedef указателя на класс QHostAddress

    const quint16 portNumber {9993} ;           ///< Порт по умолчанию по которому выполняется передача данных
    const quint32 mainWindowRefresh {1000} ;    ///< Время обновления основной формы
    const quint32 stateRefresh {5000} ;         ///< Время запроса состояния клиента/сервера

    static std::mutex mutexRefresh ;            ///< mutex для ожидания записи в модель отображения лога

    const QString textAcceptData {"Подтверждение получения данных"} ;   // Текстовое описание команд
    const QString textTransferRequest {"Запрос клиентом нового блока"} ;
    const QString textStateRequest {"Запрос состояния"} ;
    const QString textStateConfirm {"Возврат состояния"} ;
    const QString textRejectData {"Запрос отвергнут"} ;
    const QString textConnectionClose {"Соединение закрыто"} ;
    const QString textTransferData {"Передача данных"} ;
    const QString textRefuseData {"Данные отвергнуты"} ;
    const QString texError {"Произошла ошибка"} ;
    const QString textUnknown {"Неизвестная команда"} ;
}

#endif // TCOMMONDEFINE_H
