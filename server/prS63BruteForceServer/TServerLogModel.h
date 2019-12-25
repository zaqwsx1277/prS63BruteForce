#ifndef TSERVERLOGMODEL_H
#define TSERVERLOGMODEL_H

#include <QAbstractTableModel>

#include <TCommonDefaniServer.hpp>

#include <memory>


namespace server {

class TServerLogModel : public QAbstractTableModel, public std::vector <commonDefineServer::tdLogItem>
{
public:
    TServerLogModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void push_back (commonDefineServer::tdLogItem) ;  // Добавление данных в конец списка
    void refreshView () ;                   // Обновление отображения данных

private:
    enum columnNumber {cnTime = 0, cnHost, cnCommand, cnData, cnComment, cnCount} ;  // Перечень колонок в таблице

};
}

#endif // TSERVERLOGMODEL_H
