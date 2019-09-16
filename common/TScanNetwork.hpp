#ifndef TSCANNETWORK_HPP
#define TSCANNETWORK_HPP

#include <QObject>
#include <QNetworkInterface>

#include <vector>
class TScanNetwork
{

private:
    std::vector <QHostAddress> fPrtHosts ;  // Список найденных адресов

public:
    TScanNetwork();
    TScanNetwork(const QHostAddress&) ;

    std::vector <QHostAddress> getHosts () ; // Возвращает список найденных адресов
};

#endif // TSCANNETWORK_HPP
