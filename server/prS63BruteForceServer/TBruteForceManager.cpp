#include "TBruteForceManager.hpp"

#include "TCommonDefine.hpp"

using namespace server ;
//-----------------------------------------------------------
/*!
 * \brief TBruteForceManager::TBruteForceManager    Конструктор класса
 */
TBruteForceManager::TBruteForceManager() : connection::TConnectionServer ()
{
    fPtrServer.reset( new QTcpServer);
    fPtrServer->listen(QHostAddress::Any, commonDefine::portNumber) ;
}
//-----------------------------------------------------------
