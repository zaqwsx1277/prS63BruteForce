#include <QApplication>
#include <QTcpSocket>

#include <cmath>

#include "TCommonUtilitess.hpp"
#include "TCommonDefine.hpp"

//----------------------------------------------------------------------------
/*!
 * \brief commonUtilites::searchServer  Функция поиска сервера в локальной сети
 * Поск сервера выполняется только (!!!) в локальной сети на основании IP V4 адреса и маски подсети
 * \param inPort    Порт по которому ищется сервер
 * \return  Указатель на первый найденный Хост (QHostAddress). Если хост найден не будет, то возвращается nullptr
 */
commonDefine::tdHostAddress commonUtilites::searchServer (quint16 inPort)
{
    commonDefine::tdHostAddress retVal {nullptr};       // Возвращаемое значение
    bool isConnected {false} ;                          // Флаг признака найденности сервера

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
                QHostAddress ipAddressSeach = QHostAddress (ipAddressFirst + i) ;
                std::unique_ptr <QTcpSocket> ptrSocket (new QTcpSocket ()) ;
                ipServer = ipAddressSeach.toString() ;
                ptrSocket -> connectToHost(ipAddressSeach, inPort);
                connect(ptrSocket.get(), &QTcpSocket::connected, this, &unitTextMainWindow::slotHostConnected) ;
                QApplication::processEvents() ;
                if (isConnected) {
                    ptrSocket -> disconnect() ;
                    ui -> spHardwareAddress -> setText(ipServer) ;
                    break ;
                }
            }
        }
    }

}
//----------------------------------------------------------------------------
