#include "TSEmodel.hpp"
#include "TConnection.hpp"
#include "TCommonDefine.hpp"

//-----------------------------------------------------
TSEmodel::TSEmodel(QObject *parent)
{

}
//----------------------------------------------------
int TSEmodel::rowCount(const QModelIndex &parent) const
{
    return this -> size() ;
}
//----------------------------------------------------
int TSEmodel::columnCount(const QModelIndex &parent) const
{
    return columnNumber::cnCount ;
}
//----------------------------------------------------
QVariant TSEmodel::data(const QModelIndex &index, int role) const
{
    QVariant retVal = QVariant () ;
    if (index.isValid()) {

        switch (role) {             // т.к. role могут быть сымые разные, то использую switch
          case Qt::DisplayRole : {
            auto logData = this -> at(index.row()) ;    // Получаем запись из контейнере
                switch (index.column()) {               // Получаем значение для нужной колонки

                  case cnTime :
                    retVal = logData -> itemTime.toString("hh:mm:ss") ;
                  break ;

                  case cnCommand :
                    switch (logData -> itemCommand) {
                      case connection::TConnection::cmdAcceptData :
                        retVal = commonDefine::textAcceptData ;
                      break;

                      case connection::TConnection::cmdStateRequest :
                        retVal = commonDefine::textStateRequest ;
                      break ;

                      case connection::TConnection::cmdStateConfirm :
                        retVal = commonDefine::textStateConfirm ;
                      break ;

                      default:
                        retVal = commonDefine::textUnknown ;
                      break;
                    }
                  break ;

                  case cnComment :
                    retVal = logData -> comments ;
                  break ;

                  default :
                  break ;
              }
          }
          break ;

          default :         // Обработка других ролей
          break ;
        }
    }
    return retVal ;
}
//----------------------------------------------------
QVariant TSEmodel::TSEmodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant retVal = QVariant () ;
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal)
            switch (section) {
              case cnTime :
                retVal = "Время";
              break ;

              case cnCommand :
                retVal = "Команда" ;
              break ;

              case cnComment :
                retVal = "Комментарий" ;
              break ;

              default :
              break ;
            }
    return retVal ;
}
//----------------------------------------------------
void TSEmodel::push_back (seDefine::tdLogItem inItem)
{
    std::lock_guard <std::mutex> refreshWait (commonDefine::mutexRefresh) ;    // блокируем допуск остальным потокам и на обновление
    std::vector <seDefine::tdLogItem>::push_back (inItem);
}
//----------------------------------------------------
void TSEmodel::refreshView ()
{
    std::lock_guard <std::mutex> refreshWait (commonDefine::mutexRefresh) ;
    beginResetModel();
    endResetModel();
}
//----------------------------------------------------
