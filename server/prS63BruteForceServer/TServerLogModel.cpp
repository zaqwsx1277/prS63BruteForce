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

                  case cnCommand :
                    switch (logData -> command) {
                      case connection::TConnection::cmdAcceptData :
                        retVal = commonDefine::textAcceptData ;
                      break;

                      case connection::TConnection::cmdStateRequest :
                        retVal = commonDefine::textStateRequest ;
                      break ;

                      case connection::TConnection::cmdStateConfirm :
                        retVal = commonDefine::textStateConfirm ;
                      break ;

                      case connection::TConnection::cmdConnectionReject :
                        retVal = commonDefine::textRejectData ;
                      break;

                      case connection::TConnection::cmdConnectionClose :
                        retVal = commonDefine::textConnectionClose ;
                      break;

                      case connection::TConnection::cmdTransferData :
                        retVal = commonDefine::textTransferData ;
                      break;

                      case connection::TConnection::cmdRefuseData :
                        retVal = commonDefine::textRefuseData ;
                      break;

                      case connection::TConnection::cmdTransferRequest :
                        retVal = commonDefine::textTransferRequest ;
                      break;

                      case connection::TConnection::cmdError :
                        retVal = commonDefine::texError ;
                      break;

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
//----------------------------------------------------------
