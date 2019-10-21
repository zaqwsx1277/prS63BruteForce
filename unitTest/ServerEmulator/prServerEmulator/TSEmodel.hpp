#ifndef TSEMODEL_HPP
#define TSEMODEL_HPP

#include <QAbstractTableModel>

#include <memory>

#include "TSEmulatorDefine.h"
//-----------------------------------------------------------------------------
/*!
 * \brief Модель для отображения лога работы эмулятора сервера
 */
class TSEmodel : public QAbstractTableModel, public std::vector <seDefine::tdLogItem>
{
public:
    TSEmodel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void push_back (seDefine::tdLogItem) ;  // Добавление данных в конец списка
    void refreshView () ;               // Обновление отображения данных

private:
    enum columnNumber {cnTime = 0, cnCommand, cnComment, cnCount} ;  // Перечень колонок в таблице
};

#endif // TSEMODEL_HPP
