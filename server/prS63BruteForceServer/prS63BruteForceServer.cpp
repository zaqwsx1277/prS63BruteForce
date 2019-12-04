#include "prS63BruteForceServer.hpp"
#include "ui_prS63BruteForceServer.h"

#include <QRegExpValidator>
#include <QRegExp>

#include <time.h>
#include <chrono>

#include "TCommonDefine.hpp"

using namespace server ;
//------------------------------------------------------------------------------
prS63BruteForceServer::prS63BruteForceServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceServer)
{
    ui-> setupUi(this);

    initForm () ;
    fReadyToStart.reset() ;         // Очистка всех битов для контроля заполненности всех полей

    fPrtLogModel.reset( new TServerLogModel());     // Инициализируем модели отображения логов
    ui -> spLog -> setModel(fPrtLogModel.get()) ;
    for (quint8 i = 0; i < fPrtLogModel -> columnCount (); i++) {
        ui-> spLog -> horizontalHeader() -> setSectionResizeMode(i, QHeaderView::Stretch) ;
    }
    connect(ui -> spLog -> model(), &QAbstractItemModel::rowsInserted, ui -> spLog, &QTableView::scrollToBottom) ;

//    fPtrConnection.reset(new connection::TSEConnection) ;
//    setConnect () ;
}
//------------------------------------------------------------------------------
prS63BruteForceServer::~prS63BruteForceServer()
{
    delete ui;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prHackS63MainWindow::initFirm Очистка всех полей на форме
 */
void prS63BruteForceServer::initForm ()
{
    ui -> spThreadCount -> setValidator( new QRegExpValidator( QRegExp( "\\d{2}")));   // задаём все необходимые регулярные выражения
    ui -> spKeyStart -> setValidator( new QRegExpValidator( QRegExp( "[0-9A-F]")));
    ui -> spKeyStop -> setValidator( new QRegExpValidator( QRegExp( "[0-9A-F]")));

    ui -> spPathFrom -> clear() ;
    ui -> spThreadCount -> clear() ;
    ui -> spKeyStart -> clear() ;
    ui -> spKeyStop -> clear() ;
    ui -> spTimeStart -> clear() ;
    ui -> spTimeStop -> clear() ;
    ui -> spTimeDuration -> clear() ;
    ui -> spState -> clear();
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::setElementFormVisible Уcтановка видимости элементов в зависимсоти от состояния TConnection::fState
 */
void prS63BruteForceServer::setElementFormVisible ()
{

}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::checkReadyToStart  Проверка заполненности всех полей
 * \return При заполненности всех полей возвращается true
 */
bool prS63BruteForceServer::checkReadyToStart ()
{
    bool retVal = false ;
    if (fReadyToStart.all()) retVal = true ;
    return retVal ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief timerEvent    Таймер обновляющий форму
 * \param inEvent       Обрабатываемое событие
 */
void prS63BruteForceServer::timerEvent(QTimerEvent* inEvent)
{
    std::chrono::time_point<std::chrono::system_clock> nowTime = std::chrono::system_clock::now() ;
                        // Вывод продолжительности вычислений в текстовом виде
    uint32_t timeDurationSec = std::chrono::duration_cast<std::chrono::seconds> (nowTime - fTimeStart).count () % 60 ;
    QString timeDurationSecText = "00" + QString::number(timeDurationSec) ;
    uint32_t timeDurationMin = std::chrono::duration_cast<std::chrono::minutes> (nowTime - fTimeStart).count () % 60 ;
    QString timeDurationMinText = "00" + QString::number(timeDurationMin) ;
    uint32_t timeDurationHours = std::chrono::duration_cast<std::chrono::hours> (nowTime - fTimeStart).count () % 24 ;
    QString timeDurationHoursText = "00" + QString::number(timeDurationHours) ;
    uint32_t timeDurationDay = timeDurationHours / 24 ;
    QString timeDurationDayText = "00" + QString::number(timeDurationDay) ;
    QString timeDurationText = timeDurationDayText.right(2) + ":" + timeDurationHoursText.right (2) + ":" + timeDurationMinText.right(2) + ":" + timeDurationSecText.right(2) ;
    ui -> spTimeDuration -> setText(timeDurationText);
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_btnRun_clicked    Слот обрабатывающий выполнение подбора
 */
void prS63BruteForceServer::on_btnRun_clicked()
{
    fTimeStart = std::chrono::system_clock::now();      // Фиксируем время начала подбора
    startTimer(commonDefine::mainWindowRefresh) ;       // Запускаем таймер обновления


}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_spPathFrom_textChanged  Слот для проверки заполненности поля spPathFrom
 * \param inPathFrom  Проверяемое значение
 */
void prS63BruteForceServer::on_spPathFrom_textChanged(const QString &inPathFrom)
{
    if (inPathFrom.isEmpty()) fReadyToStart.reset(bitPathFrom) ;
      else fReadyToStart.set(bitPathFrom) ;
    if (checkReadyToStart ()) fPtrBruteForceManager -> setState(connection::TConnection::stReadyToStart);
      else fPtrBruteForceManager -> setState(connection::TConnection::stNotReadyToStart);
    setElementFormVisible () ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_spThreadCount_textChanged Слот для проверки заполненности поля spThreadCount
 * \param inThreadCount Проверяемое значение
 */
void prS63BruteForceServer::on_spThreadCount_textChanged(const QString &inThreadCount)
{
    if (inThreadCount.isEmpty()) fReadyToStart.reset(bitThreadCount) ;
      else fReadyToStart.set(bitThreadCount) ;
    if (checkReadyToStart ()) fPtrBruteForceManager -> setState(connection::TConnection::stReadyToStart);
      else fPtrBruteForceManager -> setState(connection::TConnection::stNotReadyToStart);
    setElementFormVisible () ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_spKeyStart_textChanged Слот для проверки заполненности поля spKeyStart
 * \param inKeyStart Проверяемое значение
 */
void prS63BruteForceServer::on_spKeyStart_textChanged(const QString &inKeyStart)
{
    if (inKeyStart.isEmpty()) fReadyToStart.reset(bitKeyStart) ;
      else fReadyToStart.set(bitKeyStart) ;
    if (checkReadyToStart ()) fPtrBruteForceManager -> setState(connection::TConnection::stReadyToStart);
      else fPtrBruteForceManager -> setState(connection::TConnection::stNotReadyToStart);
    setElementFormVisible () ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_spKeyStop_textChanged Слот для проверки заполненности поля
 * \param inKeyStop Проверяемое значение
 */
void prS63BruteForceServer::on_spKeyStop_textChanged(const QString &inKeyStop)
{
    if (inKeyStop.isEmpty()) fReadyToStart.reset(bitKeyStop) ;
      else fReadyToStart.set(bitKeyStop) ;
    if (checkReadyToStart ()) fPtrBruteForceManager -> setState(connection::TConnection::stReadyToStart);
      else fPtrBruteForceManager -> setState(connection::TConnection::stNotReadyToStart);
    setElementFormVisible () ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::closeEvent Событие для проверки возможности закрытия приложения
 * \param event Произошедшее событие
 */
void prS63BruteForceServer::closeEvent(QCloseEvent *event)
{
    switch (fPtrBruteForceManager -> getState()) {
      case connection::TConnection::stStop :
      case connection::TConnection::stNotReadyToStart :
      case connection::TConnection::stReadyToStart :
      case connection::TConnection::stWait :
        event -> accept();
      break ;

      default :
        event -> ignore() ;
      break ;
    }
}
//-----------------------------------------------------------------------------
