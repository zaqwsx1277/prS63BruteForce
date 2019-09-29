#ifndef TBRUTEFORCEMANAGER_HPP
#define TBRUTEFORCEMANAGER_HPP

#include <QTcpServer>

#include "TCommonDefine.hpp"
#include "TConnectionServer.hpp"

namespace server {
//-----------------------------------------------------------------------
/*!
 * \brief Класс выполняющий распределение блоков между клиентами
 */
class TBruteForceManager : public connection::TConnectionServer
{
public:
    TBruteForceManager();

private:
    std::shared_ptr <QTcpServer> fPtrServer {nullptr} ;   // Указатель на сервер обрабатывающий запросы клиентов
};
}
#endif // TBRUTEFORCEMANAGER_HPP
