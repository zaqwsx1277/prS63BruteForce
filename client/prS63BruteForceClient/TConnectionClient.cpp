#include "TConnectionClient.hpp"
#include "TCommonDefine.hpp"

#include <QNetworkInterface>
#include <QTcpSocket>
#include <QApplication>

#include <cmath>
#include <memory>
#include <chrono>
#include <thread>


#include <assert.h>

using namespace connection ;

//-----------------------------------------------------------
TConnectionClient::TConnectionClient()
{
    fState = TConnectionClient::stServerSearch ;    // При инициализации всегда сначала выполняется автоматический поиск сервера
    fPtrSocket.reset(new QTcpSocket ());            // После подключения к серверу соединение останется открытое
    seachServer (commonDefine::portNumber) ;
}
//-----------------------------------------------------------
void TConnectionClient::seachServer (quint16 inPort)
{
    fState = stServerSearch ;           // Установка состояния поиска сервера
    fPtrSocket -> disconnectFromHost() ;// Не задумываясь отключаюсь от сервера
    fIsServerExist = false ;
                                        // Поиск сервера
    for (auto interface : QNetworkInterface::allInterfaces()) {
        auto ipList = interface.addressEntries() ;              // Получаем список локальных IP адресов
        for (auto ipEntry : ipList) {
            auto ipEntryAddress = ipEntry.ip() ;                // Ищем IP-V4 адрес отличающийся от 127.0.0.1
            if (ipEntryAddress.isLoopback() || ipEntryAddress.isNull() || ipEntryAddress.toIPv4Address() == 0) continue ;
                                                                // Получаем параметры сети в которой находится этот IP
            auto net = QHostAddress::parseSubnet(ipEntryAddress.toString() + "/" + ipEntry.netmask().toString()) ;
            quint32 ipAddressFirst = net.first.toIPv4Address() ;
            quint32 ipAddressCount = std::pow (2, 32 - net.second) - 1 ;
                                                                // Сканируем сеть в поисках нужного сервера
            for (quint32 i = 1; i < ipAddressCount; ++i) {
                QHostAddress tmpIpAddress = QHostAddress (ipAddressFirst + i) ;
                fPtrSocket.reset(new QTcpSocket ()) ;
                fPtrSocket -> connectToHost(tmpIpAddress, inPort);   // пытаемся зацепиться за сервер и если это удается, то это обрабатывается в слоте slotHostConnected
                connect(fPtrSocket.get(), &QTcpSocket::connected, this, &TConnectionClient::slotHostConnected) ;
                std::this_thread::sleep_for(std::chrono::microseconds (100)) ;    // тормозим выполнение для нормальной обработки сигнала
                QApplication::processEvents() ;
                disconnect(fPtrSocket.get(), &QTcpSocket::connected, this, &TConnectionClient::slotHostConnected) ;
                if (fIsServerExist) {
                    fIpAddressServer = tmpIpAddress ;           // завершаем поиск после нахождения первого попавшегося сервера
                    fState = stWait ;
                    break ;
                }
            }
        }
    }
    if (!fIsServerExist) fState = stError ;
}
//-----------------------------------------------------------
/*!
 * \brief TConnectionClient::slotHostConnected  Слот обрабатывающий присоединение к серверу по указанному порту
 */
void TConnectionClient::slotHostConnected ()
{
    fIsServerExist = true ;
}
//-----------------------------------------------------------
/*!
 * \brief TConnectionClient::getIpAddressServer Получаем адрес найденного сервера
 * \return  Данные найденного сервера
 */
QHostAddress TConnectionClient::getIpAddressServer ()
{
    return fIpAddressServer ;
}
//-----------------------------------------------------------
/*!
 * \brief makeSlotConnection    Подключение всех необходимых для работы слотов
 * \param inPtrSocket   Сокет к которому подключаются слоты
 */
void TConnectionClient::makeSlotConnection (QTcpSocket* inPtrSocket)
{
    connect (inPtrSocket, &QTcpSocket::disconnected, this, &TConnectionClient::slotHostDisconnected) ;
}
//-----------------------------------------------------------
/*!
 * \brief TConnectionClient::slotServerDisconnected
 */
void TConnectionClient::slotHostDisconnected ()
{

}
//-----------------------------------------------------------

