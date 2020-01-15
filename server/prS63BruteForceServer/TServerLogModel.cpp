#include "TServerLogModel.h"

#include <QProgressDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "TCommonDefineServer.hpp"
#include "TCommonDefine.hpp"
#include "TException.hpp"
#include "TDataModule.h"

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
                    retVal = commonDefine::exchangeProtocolText [logData -> command] ;
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
    std::lock_guard <std::mutex> refreshWait (commonDefineServer::mutexLog) ;    // блокируем допуск остальным потокам к контейнеру
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
/*!
 * \brief server::prS63BruteForceServer::on_btnSave_clicked Слот обрабатывающий сохранение лога в файл
 *      При записи в файл контейнер модели отображения лога будет заблокирован, т.к. клиенты могут продолжать работать (состояние stPause).
 */
void TServerLogModel::slotSaveToFile ()
{
    try {
        if (size () == 0) throw exception::errServerFileLogEmpty ;
        QString fileName = QFileDialog::getSaveFileName(nullptr, "Выбор файла для сохранения лога подбора пароля", TDataModule::instance().fSettings -> value(commonDefine::setSrvFileNameLog).toString()) ;
        if (!fileName.isEmpty()) {
            TDataModule::instance().fSettings -> setValue(commonDefine::setSrvFileNameLog, fileName);
            QFile fileLog (fileName) ;
            if (!fileLog.open(QIODevice::WriteOnly | QIODevice::Append)) throw exception::errServerFileLog ;
            QTextStream fileLogStream (&fileLog) ;
            commonDefineServer::mutexLog.lock();            // Блокируем контейнер модели лога
            for (auto item:*this) {          // Выполняем построчную запись данных из контейнера в файл
                fileLogStream << item -> itemTime.toString () << ";" ;
                fileLogStream << item -> host << ";" ;
                fileLogStream << commonDefine::exchangeProtocolText[item -> command] << ";" ;
                QString dataTextHex = ("0000000000000000" + QString::number(item -> date, 16).toUpper()).right (16);
                fileLogStream << "0x" + dataTextHex << ";" << endl ;
                fileLogStream << item -> comments << ";" << endl ;
            }
            this -> empty() ;                       // Очищаем контейнер и снимаем блокировку
            commonDefineServer::mutexLog.unlock();
            fileLog.close();
        }

    }
    catch (exception::TException& ex) {
        commonDefineServer::mutexLog.unlock();
        QMessageBox::critical(nullptr, QString::fromStdString(exception::criticalError), QString::fromStdString(ex.what()), QMessageBox::Ok) ;
    }

    catch (...) {
        commonDefineServer::mutexLog.unlock();
        QMessageBox::critical(nullptr, QString::fromStdString(exception::criticalError), "Ошибка при сохранении лога в файл", QMessageBox::Ok) ;
    }
}
//----------------------------------------------------
