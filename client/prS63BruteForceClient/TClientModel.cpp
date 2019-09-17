#include "TClientModel.hpp"
#include "TCommonDefaneClient.hpp"

#include <thread>

//----------------------------------------------------------------------------------
/*!
 * \brief TClientModel::TClientModel    Конструктор модели
 */
client::TClientModel::TClientModel (QObject *parent, quint16 inThreadCount): QAbstractTableModel (parent)
{
    fThreadCount = (inThreadCount > maxThreads) ? maxThreads : inThreadCount ;
}
//----------------------------------------------------------------------------------
int client::TClientModel::rowCount(const QModelIndex &parent) const
{
    return this -> size() ;
}
//----------------------------------------------------------------------------------
int client::TClientModel::columnCount(const QModelIndex &parent) const
{
    return columnNumber::cnCount + std::thread::hardware_concurrency() ;
}
//----------------------------------------------------------------------------------
QVariant client::TClientModel::data(const QModelIndex &index, int role) const
{
    QVariant retVal = QVariant () ;
    if (index.isValid()) {

        switch (role) {             // т.к. role могут быть сымые разные, то использую switch
          case Qt::DisplayRole : {
            auto logData = this -> at(index.row()) ;    // Получаем запись из контейнере
            switch (index.column()) {                   // Получаем значение для нужной колонки

              case cnTime :
                retVal = logData -> timeReceiveBlock.toString("hh:mm:ss") ;
              break ;

              default :
              break ;
            }
          }
          break ;

          default :
          break ;
        }
    }

    return retVal ;
}
//---------------------------------------------------
QVariant client::TClientModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant retVal = QVariant () ;
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal)
        switch (section) {
          case cnTime :
            retVal = commonDefineClient::HeaderTimeReceiveBlock ;
          break ;

          case cnkeyFirst :
            retVal = commonDefineClient::HeaderKeyFirst ;
          break ;

//          case (fThreadCount - 1) + cnSendResult :
//            retVal = commonDefineClient::HeaderTimeSendResult ;
//          break ;

//          case (fThreadCount - 1) + cnResult:
//            retVal = commonDefineClient::HeaderResult ;
//          break ;

          default :
            retVal = QString::number(section - 2) ;
          break ;
    }

    return retVal ;
}
//---------------------------------------------------
/*!
 * \brief client::TClientModel::push_back  Добавляем в модель запись о сгенерированном числе.
 * \param inItem    Унказатель на добавляемая запись
 *
 * Обновлять данные в этот момент нельзя, т.к. при очистке контейнера софт может обновлять отображение данных и т.о. будет падать.
 */
void client::TClientModel::push_back (commonDefineClient::tdLogItemClient inItem)
{
//    std::lock_guard <std::mutex> refreshWait (exampleDefine::refresh) ;           // блокируем допуск остальным потокм на обновление

    std::vector <commonDefineClient::tdLogItemClient>::push_back(inItem);
}
//---------------------------------------------------
/*!
 * \brief client::TClientModel::refreshView Обновление отображения данных
 */
void client::TClientModel::refreshView ()
{
    beginResetModel();
    endResetModel();
}
//---------------------------------------------------
