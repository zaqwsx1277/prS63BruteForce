#ifndef TCLIENTMODEL_HPP
#define TCLIENTMODEL_HPP

#include <QAbstractTableModel>
#include <QTime>
#include <QHostAddress>

#include <vector>
#include <array>
#include <memory>

#include "TCommonDefaneClient.hpp"

namespace client {
//-----------------------------------------------------------------------------------
/*!
 * \brief The TClientModel class    Модель для отображения лога работы клиентов
 */
class TClientModel : public QAbstractTableModel, public std::vector <commonDefineClient::tdLogItemClient>
{
public:
    TClientModel(quint16 inThreadCount, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void push_back (commonDefineClient::tdLogItemClient) ;  // Добавление данных в конец списка
    void refreshView () ;               // Обновление отображения данных

private:
    enum columnNumber {cnTime = 0, cnkeyFirst, cnSendResult, cnResult, cnCount} ;  // Перечень колонок в таблице

    quint16 fThreadCount {0} ;      // Количество выделенных очередей.

public slots:
//    void slotClearModel () ;         // Удаляем все данные из модели
};

}
#endif // TCLIENTMODEL_HPP
