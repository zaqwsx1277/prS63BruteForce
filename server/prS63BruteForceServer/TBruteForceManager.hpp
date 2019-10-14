#ifndef TBRUTEFORCEMANAGER_HPP
#define TBRUTEFORCEMANAGER_HPP

#include <QTcpServer>

#include "TCommonDefine.hpp"
#include "TConnectionServer.hpp"

namespace server {
//-----------------------------------------------------------------------
/*!
 * \brief Класс выполняющий управление и распределение блоков между клиентами (в том числе локальным)
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
