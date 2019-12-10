#include "prS63BruteForceServer.hpp"
#include "ui_prS63BruteForceServer.h"

#include <QRegExpValidator>
#include <QRegExp>

#include <time.h>
#include <chrono>
#include <thread>
#include <functional>

#include <assert.h>

#include "TCommonDefine.hpp"

using namespace server ;
//------------------------------------------------------------------------------
prS63BruteForceServer::prS63BruteForceServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceServer)
{
    ui-> setupUi(this);

    assert (TConnection::cmdCount != commonDefine::exchangeProtocolText.size()) ;    // Защита от кривых рук если TConnection добавлена команда или состояние, но не добавлены их описания
    assert (TConnection::stCount != commonDefine::stateText.size()) ;

    initForm () ;
    fReadyToStart.reset() ;         // Очистка всех битов для контроля заполненности всех полей

    fPrtLogModel.reset( new TServerLogModel());     // Инициализируем модели отображения логов
    fPrtKeyModel.reset( new TServerKeyModel());
    ui -> spLog -> setModel(fPrtLogModel.get()) ;
    ui -> spLogKeys -> setModel(fPrtKeyModel.get()) ;
    for (quint8 i = 0; i < fPrtLogModel -> columnCount (); i++) {
        ui-> spLog -> horizontalHeader() -> setSectionResizeMode(i, QHeaderView::Stretch) ;
    }
    for (quint8 i = 0; i < fPrtKeyModel -> columnCount (); i++) {
        ui-> spLogKeys -> horizontalHeader() -> setSectionResizeMode(i, QHeaderView::Stretch) ;
    }
    connect(ui -> spLog -> model(), &QAbstractItemModel::rowsInserted, ui -> spLog, &QTableView::scrollToBottom) ;
    connect(ui -> spLogKeys -> model(), &QAbstractItemModel::rowsInserted, ui -> spLog, &QTableView::scrollToBottom) ;

    startTimer(commonDefineServer::timerLogRefresh) ;

    setConnect () ;                 // Инициализируем все слоты и сигналы
}
//------------------------------------------------------------------------------
/*!
 * \brief setConnect    Инициализация слотов и сигналов
 */
void prS63BruteForceServer::setConnect ()
{

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
 * \brief timerEvent    Таймер обновляющий форму и логи
 * \param inEvent       Обрабатываемое событие
 */
void prS63BruteForceServer::timerEvent(QTimerEvent* inEvent)
{
    if (getServerState () != TConnection::stWait) {     // Продолжительность подбора определяется только если сервер работает или его работа приостановлена
        std::chrono::time_point<std::chrono::system_clock> nowTime = std::chrono::system_clock::now() ;
                            // Вывод продолжительности подбора в текстовом виде
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

    ui -> spState -> setText(commonDefine::stateText [getServerState ()]) ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_btnRun_clicked    Слот обрабатывающий выполнение подбора
 */
void prS63BruteForceServer::on_btnRun_clicked()
{
    fTimeStart = std::chrono::system_clock::now();      // Фиксируем время начала подбора

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
//    if (checkReadyToStart ()) fPtrBruteForceManager -> setState(connection::TConnection::stReadyToStart);
//      else fPtrBruteForceManager -> setState(connection::TConnection::stNotReadyToStart);
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
//    if (checkReadyToStart ()) fPtrBruteForceManager -> setState(connection::TConnection::stReadyToStart);
//      else fPtrBruteForceManager -> setState(connection::TConnection::stNotReadyToStart);
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
//    if (checkReadyToStart ()) fPtrBruteForceManager -> setState(connection::TConnection::stReadyToStart);
//      else fPtrBruteForceManager -> setState(connection::TConnection::stNotReadyToStart);
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
//    if (checkReadyToStart ()) fPtrBruteForceManager -> setState(connection::TConnection::stReadyToStart);
//      else fPtrBruteForceManager -> setState(connection::TConnection::stNotReadyToStart);
    setElementFormVisible () ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::closeEvent Событие для проверки возможности закрытия приложения
 * \param event Произошедшее событие
 */
void prS63BruteForceServer::closeEvent(QCloseEvent *event)
{
//    switch (fPtrBruteForceManager -> getState()) {
//      case connection::TConnection::stStop :
//      case connection::TConnection::stNotReadyToStart :
//      case connection::TConnection::stReadyToStart :
//      case connection::TConnection::stWait :
//        event -> accept();
//      break ;

//      default :
//        event -> ignore() ;
//      break ;
//    }
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::setConnect  Формирование всех конектов
 */
void prS63BruteForceServer::setServerConnect ()
{
//    connect (fPtrConnectionServer.get(), &connection::TConnectionServer::signalHostConnected, this, &prServerEmulator::slotHostConnected) ;
//    connect (fPtrConnectionServer.get(), &connection::TConnectionServer::signalHostDisconnected, this, &prServerEmulator::slotHostDisconnected ) ;

//    connect (fPtrConnectionServer.get(), &connection::TConnectionServer::signalHostConnected, this, &prS63BruteForceServer::slotHostConnected) ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::slotHostConnected Слот срабатывающий при подключении нового клиента. Сигнал кидается из TConnectionServer
 * \param inTcpSocket Указатель на сокет с новым подключением клиента
 */
void prS63BruteForceServer::slotHostConnected (QTcpSocket *inTcpSocket)
{
    std::lock_guard <std::mutex> connectionWait (commonDefineServer::mutexNewConnection) ;    // Блокируем допуск к контейнеру новых подключений. Это необходимо что бы не запустилось два потока для обработки подключений
    commonDefineServer::tdClientDescr ptrClientDescr ;
    ptrClientDescr -> ptrTcpSocket.reset(inTcpSocket); ;
    fConnectionQueue.push(ptrClientDescr);
    if (fConnectionQueue.size() == 1) {           // Запускаем поток обрабатывающий новые входящие подключения. Поток будет работать до тех пор, пока не обработает все записи в контейнере
//        std::thread manager (&prS63BruteForceServer::connectionManager) ;
//        manager.detach();
    }
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::connectionManager  Менеджер обработки входящих соединений. Менеджер обрабатывает все записи в fConnectionQueue в который в прцессе обработки могут добавляться новые записи
 */
void prS63BruteForceServer::connectionManager ()
{
    while (!fConnectionQueue.empty()) {
        commonDefineServer::tdClientDescr ptrClientDescr = fConnectionQueue.front () ; // Вынимаем из контейнера запись о клиенте
        fConnectionQueue.pop () ;
//        connect(ptrClientDescr -> ptrTcpSocket.get(), &QTcpSocket::readyRead, this, &prS63BruteForceServer::readDataFromClient) ;   // Формируем все нужные коннекты для работы с клиентом
        // Отправляем клиенту подтверждение о подключении
        // Ждём ответ от клиента
        // Если ответ от клиента поступил, то переносим запись о клиенте в контейнер содержащие записи о всех подключенных клиентах
        // Если ответ не поступил, то запись о клиенте просто умирает
    }
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::getServerState Получение состояния сервера
 * \return Состояние сервера
 */
TConnection::state prS63BruteForceServer::getServerState ()
{
    TConnection::state retVal {TConnection::stUnknown} ;
    if (fPtrConnectionServer != nullptr) retVal = fPtrConnectionServer -> getState() ;
      else retVal = TConnection::stWait ;

    return retVal ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::setServerState Установка состояния сервера
 * \param inState   Устанавливаемое состояние
 */
void prS63BruteForceServer::setServerState(TConnection::state inState)
{
    fPtrConnectionServer ->setState (inState) ;
}
//-----------------------------------------------------------------------------
