#include "TConnectionClient.hpp"
#include "TCommonDefine.hpp"

#include <QNetworkInterface>
#include <QTcpSocket>
#include <QApplication>

#include <cmath>
#include <memory>
//-----------------------------------------------------------
TConnectionClient::TConnectionClient()
{

}
//-----------------------------------------------------------
void TConnectionClient::seachServer ()
{
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
                ptrSocket -> connectToHost(ipAddressSeach, commonDefine::portNumber);   // пытаемся зацепиться за сервер и если это удается, то это обрабатывается в слоте slotHostConnected
                connect(ptrSocket.get(), &QTcpSocket::connected, this, &TConnectionClient::slotHostConnected) ;
                QApplication::processEvents() ;
            }
        }
    }
}
//-----------------------------------------------------------
void TConnectionClient::slotHostConnected ()
{

}
//-----------------------------------------------------------
