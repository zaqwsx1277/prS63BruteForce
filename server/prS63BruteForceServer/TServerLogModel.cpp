#include "TServerLogModel.h"


#include "TCommonDefaneServer.hpp"
using namespace server ;

//--------------------------------------------------------
TServerLogModel::TServerLogModel(QObject *parent)
{

}
//----------------------------------------------------------
int TServerLogModel::rowCount(const QModelIndex &parent) const
{
    return this -> size() ;
}
//----------------------------------------------------------
int TServerLogModel::columnCount(const QModelIndex &parent) const
{
    return columnNumber::cnCount ;
}
//----------------------------------------------------------
QVariant TServerLogModel::data(const QModelIndex &index, int role) const
{
    QVariant retVal = QVariant () ;
    if (index.isValid()) {

        switch (role) {             // т.к. role могут быть сымые разные, то использую switch
          case Qt::DisplayRole : {
             commonDefineServer::tdLogItem logData = this -> at(index.row()) ;    // Получаем запись из контейнера
                switch (index.column()) {               // Получаем значение для нужной колонки

                  case cnTime :
                    retVal = logData -> itemTime.toString("hh:mm:ss") ;
                  break ;

                  case cnHost :
                    retVal = logData -> host ;
                  break ;

                  case cnCommand :
                    retVal = connection::exchangeProtocolText [logData -> command] ;
                  break ;

                  case cnData :
                    retVal = QString::number(logData -> date) ;
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
//----------------------------------------------------------
QVariant TServerLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
        QVariant retVal = QVariant () ;
        if (role != Qt::DisplayRole) return QVariant();

        if (orientation == Qt::Horizontal)
                switch (section) {
                  case cnTime :
                    retVal = commonDefineServer::logItemHeaderTime ;
                  break ;

                  case cnHost :
                    retVal = commonDefineServer::logItemHeaderHost ;
                  break ;

                  case cnCommand :
                    retVal = commonDefineServer::logItemHeaderCommand ;
                  break ;

                  case cnData :
                    retVal = commonDefineServer::logItemHeaderData ;
                  break ;

                  case cnComment :
                    retVal = commonDefineServer::logItemHeaderComment ;
                  break ;

                  default :
                  break ;
                }
        return retVal ;
}
//----------------------------------------------------------
void TServerLogModel::push_back (commonDefineServer::tdLogItem inItem)
{
    std::lock_guard <std::mutex> refreshWait (commonDefineServer::mutexLog) ;    // блокируем допуск остальным потокам и на обновление
    std::vector <commonDefineServer::tdLogItem>::push_back (inItem);
}
//----------------------------------------------------
void TServerLogModel::refreshView ()
{
    std::lock_guard <std::mutex> refreshWait (commonDefineServer::mutexLog) ;
    beginResetModel();
    endResetModel();
}
//----------------------------------------------------
