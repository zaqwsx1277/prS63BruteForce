#ifndef TTESTDECRYPTLOGMODEL_HPP
#define TTESTDECRYPTLOGMODEL_HPP

#include <QAbstractTableModel>

#include <vector>

#include "TTestDecryptCommon.hpp"

namespace unitTest {

class TTestDecryptLogModel : public QAbstractTableModel, std::vector <tdPtrTestDecryptLogData>
{
public:
    TTestDecryptLogModel(QObject *parent = nullptr) ;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex ()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void push_back(tdPtrTestDecryptLogData);    // Запись данных в контейнер

private:

    enum posTbl {   // Номера позиций в таблице лога
        posFileName = 0,    //  Имя файла
        posKey = 1,         //  Ключ
        posInData = 2,      // Первые 8 байт из файла
        posOutData = 3,     // Расшифрованные первые 8  байт
        posResult = 4,      // Результат получения файла S57
        posCount,           // Количество столбцов в таблице
    } ;
};

}
#endif // TTESTDECRYPTLOGMODEL_HPP
