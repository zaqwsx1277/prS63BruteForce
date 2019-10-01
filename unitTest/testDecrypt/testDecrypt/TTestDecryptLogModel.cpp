#include "TTestDecryptLogModel.hpp"

using namespace unitTest ;
//--------------------------------------------------------------
TTestDecryptLogModel::TTestDecryptLogModel(QObject *parent) : QAbstractTableModel (parent)
{

}
//--------------------------------------------------------------
int TTestDecryptLogModel::rowCount(const QModelIndex& parent) const
{
    return this -> size() ;     // Возвращаем размер вектора
}
//--------------------------------------------------------------
int TTestDecryptLogModel::columnCount(const QModelIndex& parent) const
{
    return posCount ;           // Возвращаем количество колонок
}
//--------------------------------------------------------------
QVariant TTestDecryptLogModel::data(const QModelIndex& index, int role) const
{
    QVariant retVal {QVariant()} ;

    if (index.isValid()) {
        tdPtrTestDecryptLogData logData = at (index.row()) ;
        switch (role) {
          case Qt::DisplayRole :    // Вывод данных
            switch (index.column()) {
              case posFileName:
                retVal = logData -> fileName ;
              break ;

              case posKey:
                retVal = logData -> key ;
              break ;

              case posInData :
                retVal = logData -> inData ;
              break ;

              case posOutData :
                retVal = logData -> outData ;
              break ;

              case posResult :
                if (logData -> result) retVal = "Выполнен успешно" ;
                  else retVal = "Ошибка" ;
              break ;

              default :
              break ;
            }
          break ;

          default :
          break ;
        }
    }
    return retVal ;
}
//--------------------------------------------------------------
QVariant TTestDecryptLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant retVal = QVariant () ;

    if (orientation == Qt::Horizontal) {
        switch (role) {
          case Qt::DisplayRole :    // Вывод горизонтальных заголовков
            switch (section) {
              case posFileName:
                retVal = "Имя файла";
               break ;

              case posKey:
                retVal = "Ключ" ;
              break ;

              case posInData :
                retVal = "Первые 8 байт";
              break ;

              case posOutData :
                retVal = "Расшифрованные\n8 байт" ;
              break ;

              case posResult :
                retVal = "Результат расшифровки\nфайла" ;
              break ;

              default :
              break ;
            }
          break ;

          default:
          break ;
        }
    }

    return retVal ;
}
//--------------------------------------------------------------
/*!
 * \brief TTestDecryptLogModel::push_back   Запись данных в контейнер
 */
void TTestDecryptLogModel::push_back(tdPtrTestDecryptLogData inData)
{
    std::vector <tdPtrTestDecryptLogData>::push_back(inData) ;

    beginInsertRows(QModelIndex(), size (), size()) ;
    endInsertRows() ;
}
//--------------------------------------------------------------
