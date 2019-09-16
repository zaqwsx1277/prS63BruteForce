#include "TClientModel.hpp"

#include <thread>

//----------------------------------------------------------------------------------
/*!
 * \brief TClientModel::TClientModel    Конструктор модели
 */
client::TClientModel::TClientModel (QObject *parent): QAbstractTableModel (parent)
{

}
//----------------------------------------------------------------------------------
void client::TClientModel::rowCount(const QModelIndex &parent) const
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
            std::vector <client::TLogItemClient> logData = this -> at(index.row()) ;    // Получаем указатель на запись в контейнере
            switch (index.column()) {                                                   // Получаем значение для нужной колонки

              case cnTime :
                retVal = logData.time.toString("hh:mm:ss") ;
              break ;

              case cnThreadId : {
                std::stringstream threadId ;
                threadId << logData.threadId ;
                retVal = QString::fromStdString(threadId.str ()) ;
              }
              break ;

              case cnNumeric :
                if (logData.numeric == 0) retVal = "" ;
                  else retVal = logData.numeric ;
              break ;

              case cnReasonExit :
                retVal = logData.reasonExit ;
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
QVariant TExample1LogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant retVal = QVariant () ;
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal)
        switch (section) {
          case cnNumLine :
            retVal = "" ;
          break ;

          case cnTime :
            retVal = exampleDefine::example1HeaderTime ;
          break ;

          case cnThreadId :
            retVal = exampleDefine::example1HeaderThreadId ;
          break ;

          case cnNumeric :
            retVal = exampleDefine::example1HeaderNumeric ;
          break ;

          case cnReasonExit :
            retVal = exampleDefine::example1HeaderReasonExit ;
          break ;

          default :
          break ;
    }

    return retVal ;
}
//---------------------------------------------------
/*!
 * \brief TExample1LogModel::slotClearModel Слот очищающий модель
 */
void TExample1LogModel::slotClearModel ()
{
    beginRemoveRows (QModelIndex(), 0, this ->size() - 1);
    std::vector <exampleDefine::example1LogData>::clear() ;
    endRemoveRows();
}
//---------------------------------------------------
/*!
 * \brief TExample1LogModel::push_back  Добавляем в модель запись о сгенерированном числе.
 * \param inItem    Добавляемая запись
 *
 * Обновлять данные в этот момент нельзя, т.к. при очистке контейнера софт может обновлять отображение данных и т.о. будет падать.
 */
void TExample1LogModel::push_back (exampleDefine::example1LogData inItem)
{
    std::lock_guard <std::mutex> refreshWait (exampleDefine::refresh) ;           // блокируем допуск остальным потокм на обновление

    inItem.numLine = exampleDefine::logNumLine.fetch_add (1) + 1 ;
    if ((inItem.numLine  % exampleDefine::logLineMaxCount) == 0) slotClearModel () ;

    std::vector <exampleDefine::example1LogData>::push_back(inItem);
}
//---------------------------------------------------
/*!
 * \brief TExample1LogModel::refreshView Обновление отображения данных
 */
void TExample1LogModel::refreshView ()
{
    beginResetModel();
    endResetModel();
}
//---------------------------------------------------
