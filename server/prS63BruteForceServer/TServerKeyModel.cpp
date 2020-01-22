#include "TServerKeyModel.h"

#include "TCommonDefineServer.hpp"
using namespace server ;

//----------------------------------------------------------------------
TServerKeyModel::TServerKeyModel (QObject *parent)
{

}
//----------------------------------------------------------------------
int TServerKeyModel::rowCount(const QModelIndex &parent) const
{
    return this -> size() ;
}
//----------------------------------------------------
int TServerKeyModel::columnCount(const QModelIndex &parent) const
{
    return columnNumber::cnCount ;
}
//----------------------------------------------------
QVariant TServerKeyModel::data(const QModelIndex &index, int role) const
{
    QVariant retVal = QVariant () ;
    if (index.isValid()) {

        switch (role) {             // т.к. role могут быть сымые разные, то использую switch
          case Qt::DisplayRole : {
            auto logData = this -> at(index.row()) ;    // Получаем запись из контейнерa
                switch (index.column()) {               // Получаем значение для нужной колонки

                  case cnTime :
                    retVal = logData -> itemTime.toString("hh:mm:ss") ;
                  break ;


                  case cnHost:
                    retVal = logData -> host ;
                  break ;

                  case cnKey :
                    retVal = logData -> key ;
                  break ;

                  case cnResult :
                    retVal = logData -> result ;
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
QVariant TServerKeyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant retVal = QVariant () ;
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal)
            switch (section) {
              case cnTime :
                retVal = commonDefineServer::keyItemHeaderTime ;
              break ;

              case cnHost :
                retVal = commonDefineServer::keytemHeaderHost ;
              break ;

              case cnKey :
                retVal = commonDefineServer::keyItemHeaderKey ;
              break ;

              case cnResult :
                retVal = commonDefineServer::keyItemHeaderResult ;
              break ;

              default :
              break ;
            }
    return retVal ;
}
//----------------------------------------------------
void TServerKeyModel::push_back (commonDefineServer::tdKeyItem inItem)
{
    std::unique_lock <std::mutex> refreshWait (commonDefineServer::mutexKey) ;// блокируем допуск остальным потокaм на работу с контейнером
    commonDefineServer::cvKey.wait(refreshWait , [] { return !commonDefineServer::isKeyBlock ; });
    commonDefineServer::isKeyBlock = true ;

    std::vector <commonDefineServer::tdKeyItem>::push_back (inItem);
    commonDefineServer::isKeyBlock = true ;
    commonDefineServer::cvKey.notify_one();
}
//----------------------------------------------------
/*!
 * \brief TServerKeyModel::refreshView  Обновление лога подбора ключей
 *      Блокировка commonDefineServer::mutexKey, снятие блокировки и уведомления заблокированных потоков должны выполняться до вызова обновления
 */
void TServerKeyModel::refreshView ()
{
    beginResetModel();
    endResetModel();
}
//----------------------------------------------------
