#include "prS63BruteForceServer.hpp"
#include "ui_prS63BruteForceServer.h"

#include <QRegExpValidator>
#include <QRegExp>

#include <time.h>
#include <chrono>

#include "TCommonDefine.hpp"

//------------------------------------------------------------------------------
prS63BruteForceServer::prS63BruteForceServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceServer)
{
    ui->setupUi(this);

    initForm () ;
    fReadyToStart.reset() ;         // Очистка всех битов для контроля заполненности всех полей
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
 * \brief prS63BruteForceServer::serverStart    Запуск сервера для распределенной работы
 * \return В случае ошибки запуска возвращается false
 */
bool prS63BruteForceServer::serverStart ()
{

}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::serverStop     Останов сервера для распределенной работы
 * \return В случае ошибки запуска возвращается false
 */
bool prS63BruteForceServer::serverStop ()
{

}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::serverPause    Приостановка работы сервера для распределенной работы
 * \return В случае ошибки запуска возвращается false
 */
bool prS63BruteForceServer::serverPause ()
{

}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::bruteForceManagerStart Запуск менеджера распределения ключей
 * \return В случае ошибки запуска возвращается false
 */
bool prS63BruteForceServer::bruteForceManagerStart ()
{

}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::bruteForceManagerStop  Останов менеджера распределения ключей
 * \return В случае ошибки запуска возвращается false
 */
bool prS63BruteForceServer::bruteForceManagerStop ()
{

}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::bruteForceManagerPause Приостановка работы менеджера распределения ключей
 * \return В случае ошибки запуска возвращается false
 */
bool prS63BruteForceServer::bruteForceManagerPause ()
{

}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_spPathFrom_textChanged  Слот для проверки заполненности поля обрабатываемого файла
 * \param inPathFrom  Проверяемое значение
 */
void prS63BruteForceServer::on_spPathFrom_textChanged(const QString &inPathFrom)
{
    if (inPathFrom.isEmpty()) fReadyToStart.reset(0) ;
      else fReadyToStart.set(0) ;
    if (checkReadyToStart ()) fPtrConnectionServer -> setState(TConnection::stReadyToStart);
      else fPtrConnectionServer -> setState(TConnection::stNotReadyToStart);
}
//-----------------------------------------------------------------------------
