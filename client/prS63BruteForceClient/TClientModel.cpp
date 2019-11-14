#include "TClientModel.hpp"
#include "TCommonDefaneClient.hpp"

#include <thread>
#include <mutex>

#include "TCommonDefine.hpp"

//----------------------------------------------------------------------------------
/*!
 * \brief TClientModel::TClientModel    Конструктор модели
 */
client::TClientModel::TClientModel (quint16 inThreadCount, QObject *parent): QAbstractTableModel (parent)
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
    return columnNumber::cnCount + fThreadCount ;
}
//----------------------------------------------------------------------------------
QVariant client::TClientModel::data(const QModelIndex &index, int role) const
{
    QVariant retVal = QVariant () ;
    if (index.isValid()) {

        switch (role) {             // т.к. role могут быть сымые разные, то использую switch
          case Qt::DisplayRole : {
            auto logData = this -> at(index.row()) ;    // Получаем запись из контейнере
            if (index.column() < (fThreadCount + 3)) {  // Выводим первую секцию данных + номера данные потоков кол-во которых может быть переменным
                switch (index.column()) {               // Получаем значение для нужной колонки

                  case cnTime :
                    retVal = logData -> timeReceiveBlock.toString("hh:mm:ss") ;
                  break ;

                  case cnComment :
                    retVal = logData -> comment ;
                  break ;

                  default :
                  break ;
                }
            }
            else {
                switch (index.column()) {


                  default :
                  break ;
                }
            }
            break ;
          }

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
        if (section < (fThreadCount + 3)) {     // Выводим первую секцию заголовков + номера потоков кол-во которых может быть переменным
            switch (section) {
              case cnTime :
                retVal = commonDefineClient::HeaderTimeReceiveBlock ;
              break ;

              case cnkeyFirst :
                retVal = commonDefineClient::HeaderKeyFirst ;
              break ;

              case cnComment :
                retVal = commonDefineClient::HeaderComment ;
              break ;

              default :
                retVal = QString::number(section - 3) ;
              break ;
            }
        }
        else {                                  // Выводим последнюю секцию заголовков
            switch (section - fThreadCount) {
              case cnSendResult :
                retVal = commonDefineClient::HeaderTimeSendResult ;
              break ;

              case cnResult :
                retVal = commonDefineClient::HeaderResult ;
              break ;


              default :
              break ;
            }
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
    std::lock_guard <std::mutex> refreshWait (commonDefine::mutexRefresh) ;    // блокируем допуск остальным потокам на обновление
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
