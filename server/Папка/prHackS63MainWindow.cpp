#include "prHackS63MainWindow.hpp"
#include "ui_prHackS63MainWindow.h"

#include <QRegExpValidator>
#include <QRegExp>

#include <time.h>

#include "TCommonDefine.hpp"

//------------------------------------------------------------------------------
prHackS63MainWindow::prHackS63MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prHackS63MainWindow)
{
    ui->setupUi(this);

    initForm () ;
}
//------------------------------------------------------------------------------
prHackS63MainWindow::~prHackS63MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prHackS63MainWindow::initFirm Очистка всех полей на форме
 */
void prHackS63MainWindow::initForm ()
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
 * \brief timerEvent    Таймер обновляющий форму
 * \param inEvent       Обрабатываемое событие
 */
void prHackS63MainWindow::timerEvent(QTimerEvent* inEvent)
{
    std::time_t timeDuration = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() - fTimeStart); // Вычисляем продолжительность подбора
    auto xx1 = localtime (&timeDuration)-> tm_mday;
    auto xx2 = localtime (&timeDuration)-> tm_hour;

    int i = 0 ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prHackS63MainWindow::on_btnRun_clicked    Слот обрабатывающий выполнение подбора
 */
void prHackS63MainWindow::on_btnRun_clicked()
{
    fTimeStart = std::chrono::system_clock::now();      // Фиксируем время начала подбора
    startTimer(commonDefine::mainWindowRefresh) ;       // Запускаем таймер обновления
}
//-----------------------------------------------------------------------------
