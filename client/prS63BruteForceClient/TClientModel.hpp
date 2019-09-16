#ifndef TCLIENTMODEL_HPP
#define TCLIENTMODEL_HPP

#include <QAbstractTableModel>
#include <QTime>
//#include <QtGlobal>

#include <vector>
#include <array>

namespace client {

#define maxThreads 256 ;    // Максимальное количество потоков. Нужно для обеспечения максимальной производительности подбора и поэтому с модели используется std::array

struct TLogItemClient
{
    QTime receiveBlock ;    // Время получения начального значения ключа
    quint64 keyFirst {0} ;  // Первый ключ в блоке
    std::array <quint64, 256> keys {0} ; // обрабатываемые ключи
    QTime sendResult ;      // Время передачи результата
    QString result {""} ;   // 0 - если подобранных ключей нет, или список подобранных ключей разделённых запятой
};

//-----------------------------------------------------------------------------------
/*!
 * \brief The TClientModel class    Модель для отображения лога работы клиентв
 */
class TClientModel : public QAbstractTableModel, public std::vector <client::TLogItemClient>
{
public:
    TClientModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void push_back (client::TLogItemClient) ;  // Добавление данных в конец списка
    void refreshView () ;           // Обновление отображения данных

private:
    enum columnNumber {cnTime = 0, cnkeyFirst, cnSendResult, cnResult, cnCount} ;  // Перечень колонок в таблице

public slots:
    void slotClearModel () ;         // Удаляем все данные из модели
};

}
#endif // TCLIENTMODEL_HPP
