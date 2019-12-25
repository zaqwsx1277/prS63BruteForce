#ifndef TSERVERKEYMODEL_H
#define TSERVERKEYMODEL_H

#include <QAbstractTableModel>

#include <TCommonDefaniServer.hpp>

#include <memory>


namespace server {
class TServerKeyModel : public QAbstractTableModel, public std::vector <commonDefineServer::tdKeyItem>
{
public:
    TServerKeyModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void push_back (commonDefineServer::tdKeyItem) ;// Добавление данных в конец списка
    void refreshView () ;                           // Обновление отображения данных

private:
    enum columnNumber {cnTime = 0, cnHost, cnKey, cnResult, cnCount} ;  // Перечень колонок в таблице

};
};

#endif // TSERVERKEYMODEL_H
