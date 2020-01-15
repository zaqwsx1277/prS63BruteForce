#include "prS63BruteForceServer.hpp"
#include "ui_prS63BruteForceServer.h"

#include <QRegExpValidator>
#include <QRegExp>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QSettings>

#include <time.h>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>

#include <assert.h>

#include "TCommonDefine.hpp"
#include "TException.hpp"
#include "TDataModule.h"

using namespace server ;
//------------------------------------------------------------------------------
prS63BruteForceServer::prS63BruteForceServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceServer)
{
    ui-> setupUi(this);

    assert (TConnection::cmdCount == commonDefine::exchangeProtocolText.size()) ;    // Защита от кривых рук если TConnection добавлена команда или состояние, но не добавлены их описания
    assert (TConnection::stCount == commonDefine::stateText.size()) ;

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
    connect(ui -> btnSave, &QPushButton::clicked, fPrtLogModel.get(), &TServerLogModel::slotSaveToFile) ;   // Сохранение лога в файл
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
    ui -> spBlockSize -> setValidator( new QRegExpValidator( QRegExp( "\\d{6}")));   // задаём все необходимые регулярные выражения
    ui -> spKeyStart -> setValidator( new QRegExpValidator( QRegExp( "[0-9A-F]{8}")));
    ui -> spKeyStop -> setValidator( new QRegExpValidator( QRegExp( "[0-9A-F]{8}")));
                                // читаем файл настроек и заполняем нужные поля
    ui -> spPathFrom -> setText(TDataModule::instance().fSettings -> value(commonDefine::setSrvFileName).toString()) ;
    ui -> spKeyStart -> setText(TDataModule::instance().fSettings -> value(commonDefine::setSrvKeyStart).toString()) ;
    ui -> spKeyStop -> setText(TDataModule::instance().fSettings-> value(commonDefine::setSrvKeyStop).toString()) ;
    if (ui -> spKeyStart -> text().isEmpty()) ui -> spKeyStart -> setText ("00000000") ;
    if (ui -> spKeyStop -> text().isEmpty()) ui -> spKeyStop -> setText ("FFFFFFFF") ;

    ui -> spBlockSize-> clear() ;

    ui -> spTimeStop -> clear() ;
    ui -> spTimeStart -> clear();
    ui -> spTimeDuration -> clear() ;
    ui -> spState -> clear();

    setElementFormVisible () ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::setElementFormVisible Уcтановка видимости элементов в зависимсоти от состояния TConnection::fState
 */
void prS63BruteForceServer::setElementFormVisible ()
{
    switch (getServerState ()) {
      case connection::TConnection::stWait :
        if (fReadyToStart.all()) ui -> btnRun -> setEnabled(true) ;     // Проверяем заполненность всех полей
          else ui -> btnRun -> setEnabled(false) ;
        ui -> btnSave -> setEnabled (true) ;
        ui -> btnStop -> setEnabled(true) ;

        ui -> btnRun -> setIcon(QIcon (":/icones/icones/run.png")) ;

        ui -> btnRun -> setToolTip(commonDefineServer::toolTipRun);
        ui -> btnStop -> setToolTip(commonDefineServer::toolTipExit);

        ui -> spPathFrom -> setEnabled (true) ;
        ui -> spBlockSize -> setEnabled (true) ;
        ui -> spKeyStart -> setEnabled (true) ;
        ui -> spKeyStop -> setEnabled (true) ;
      break ;

      case connection::TConnection::stStart :
        ui -> spPathFrom -> setEnabled (false) ;
        ui -> spBlockSize-> setEnabled (false) ;
        ui -> spKeyStart -> setEnabled (false) ;
        ui -> spKeyStop -> setEnabled (false) ;

        ui -> btnSave -> setEnabled (false) ;
        ui -> btnStop -> setEnabled(true);

        ui -> btnRun -> setIcon(QIcon (":/icones/icones/pause.png")) ;

        ui -> btnRun -> setToolTip(commonDefineServer::toolTipPause);
        ui -> btnStop -> setToolTip(commonDefineServer::toolTipStop);
      break ;

      case connection::TConnection::stPause :
        ui -> spPathFrom -> setEnabled (false) ;
        ui -> spBlockSize -> setEnabled (false) ;
        ui -> spKeyStart -> setEnabled (false) ;
        ui -> spKeyStop -> setEnabled (false) ;

        ui -> btnSave -> setEnabled (true) ;
        ui -> btnStop -> setEnabled(true);

        ui -> btnRun -> setIcon(QIcon (":/icones/icones/run.png")) ;
        ui -> btnRun -> setToolTip(commonDefineServer::toolTipRun);
        ui -> btnStop -> setToolTip(commonDefineServer::toolTipStop);
      break ;

      case connection::TConnection::stAppClose :                        // Ожидаем окончания всех очередей и поэтому выключаем все элементы
      case connection::TConnection::stStop :
      case connection::TConnection::stUnknown :                         // Абсолютно непонятное состояние и поэтому тоже выключаем все кнопки
      default :
        ui -> spPathFrom -> setEnabled (false) ;
        ui -> spBlockSize -> setEnabled (false) ;
        ui -> spKeyStart -> setEnabled (false) ;
        ui -> spKeyStop -> setEnabled (false) ;

        ui -> btnSave -> setEnabled (false) ;
        ui -> btnStop -> setEnabled(false);
      break ;
    }
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
 * \brief prS63BruteForceServer::closeEvent Событие для проверки возможности закрытия приложения
 * \param event Произошедшее событие
 */
void prS63BruteForceServer::closeEvent(QCloseEvent *event)
{
            // Т.к. при использовании регулярных выражений не срабарывают сигналы на окончание редактирования, то сохранение настроек приделал сюда
    TDataModule::instance().fSettings -> setValue(commonDefine::setSrvKeyStart, ui-> spKeyStart -> text()) ;
    TDataModule::instance().fSettings -> setValue(commonDefine::setSrvKeyStop, ui-> spKeyStop -> text()) ;

    switch (getServerState ()) {
      case connection::TConnection::stWait :
      case connection::TConnection::stUnknown :
        event -> accept();          // Т.к. ожидается, что в этом режиме все потоки завершены, то просто закрываем приложение
      break ;

      case connection::TConnection::stStop :
      case connection::TConnection::stPause :
        setServerState(TConnection::stAppClose);
        waitAllThread () ;          // Ожидаем завершение всех потоков
        event -> accept();
      break ;

      case connection::TConnection::stStart : {
        int isExit = QMessageBox::warning (this, "Предупреждение", "Выполняется подбор паролей.\nЗавершить приложение?", QMessageBox::Ok | QMessageBox::No, QMessageBox::No) ;
        if (isExit == QMessageBox::Ok) {
            setServerState(TConnection::stAppClose);
            waitAllThread () ;          // Ожидаем завершение всех потоков
            event -> accept();
        }
          else event -> ignore() ;
      }
      break ;

      default :
        event -> ignore() ;
      break ;
    }
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::setConnect  Формирование всех конектов
 */
void prS63BruteForceServer::makeConnectServer ()
{
    connect (fPtrNewConnection.get(), &connection::TConnectionServer::signalNewHostConnected , this, &prS63BruteForceServer::slotNewHostConnected ) ;
//    connect (fPtrConnectionServer.get(), &connection::TConnectionServer::signalHostDisconnected, this, &prServerEmulator::slotHostDisconnected ) ;

//    connect (fPtrConnectionServer.get(), &connection::TConnectionServer::signalHostConnected, this, &prS63BruteForceServer::slotHostConnected) ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::slotHostConnected Слот срабатывающий при подключении нового клиента. Сигнал кидается из TConnectionServer
 * \param inTcpSocket Указатель на сокет с новым подключением клиента
 */
void prS63BruteForceServer::slotNewHostConnected (QTcpSocket *inTcpSocket)
{
    std::lock_guard <std::mutex> newConnection (commonDefineServer::mutexNewConnection) ;    // Блокируем допуск к контейнеру новых подключений. Это необходимо что бы не запустилось два потока для обработки подключений
    commonDefineServer::tdClientDescr ptrClientDescr ;
    ptrClientDescr -> ptrTcpSocket.reset(inTcpSocket);
    fNewConnectionQueue.push(ptrClientDescr);
    if (fNewConnectionQueue.size() == 1) {           // Запускаем поток обрабатывающий новые входящие подключения. Поток будет работать до тех пор, пока не обработает все записи в контейнере
        std::thread manager (std::bind (&prS63BruteForceServer::newConnectionManager, this)) ;
        manager.detach();
    }
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::connectionManager  Менеджер обработки входящих соединений. Менеджер обрабатывает все записи в fConnectionQueue в который в прцессе обработки могут добавляться новые записи
 */
void prS63BruteForceServer::newConnectionManager ()
{
    while (!fNewConnectionQueue.empty()) {
        commonDefineServer::mutexNewConnection.lock();                                  // Блокируем доступ к контейнеру новых подключений
        commonDefineServer::tdClientDescr ptrClientDescr = fNewConnectionQueue.front () ;  // Вынимаем из контейнера запись о клиенте
        fNewConnectionQueue.pop () ;
        commonDefineServer::mutexNewConnection.unlock();

        std::unique_ptr <TConnection> newConnection {new TConnection (ptrClientDescr -> ptrTcpSocket.get())} ;
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
    if (fPtrNewConnection!= nullptr) retVal = fPtrNewConnection -> getState() ;
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
    if (fPtrNewConnection != nullptr) {
        fPtrNewConnection -> setState (inState) ;
        setElementFormVisible () ;
    }
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::waitAllThread  Ожидание завершение всех очередей
 *      Т.к. мы ожидаем завершения приложения, то в данном методе ЗАПРЕЩЕНО обрабатывать какие-либо сообщения и
 *          поэтому QApplication::processEvents() вызывать нельзя.
 */
void prS63BruteForceServer::waitAllThread ()
{
    if (fPtrNewConnection != nullptr)
        if (fPtrNewConnection -> getState() == TConnection::stAppClose) {    // Запуск ожидания возможен только при состоянии TConnection::stAppClose

        }
}
//-----------------------------------------------------------------------------
/*!
 * \brief server::prS63BruteForceServer::on_btnPathFrom_clicked Слот выбора обрабатываемого файла
 */
void server::prS63BruteForceServer::on_btnPathFrom_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выбор файла для подбора пароля", "", "S63 (*.0*)");
    if (!fileName.isEmpty()) {
        ui -> spPathFrom -> setText(fileName) ;
        TDataModule::instance().fSettings -> setValue(commonDefine::setSrvFileName, fileName);
    }
}
//-----------------------------------------------------------------------------
/*!
 * \brief server::prS63BruteForceServer::on_btnStop_clicked Слот обрабатывающий нажатие кнопки останова
 */
void server::prS63BruteForceServer::on_btnStop_clicked()
{
    switch (getServerState ()) {
      case TConnection::stWait :
        this -> close() ;
      break ;

      case TConnection::stStart :
        setServerState(TConnection::stStop);
        waitAllThread () ;                      // Ожидаем завершение всех очередей
        fPtrNewConnection.reset(nullptr);    // Т.к. в теории все очереди завершены, то тупо очищаем все соединения
        setServerState(TConnection::stWait);
      break ;

      default :
      break ;
    }
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_btnRun_clicked    Слот обрабатывающий запуск сервера
 */
void prS63BruteForceServer::on_btnRun_clicked()
{
    try {
        switch (getServerState ()) {    // Выполняем действия в зависимости от состояния
            case TConnection::stWait :
                fTimeStart = std::chrono::system_clock::now();      // Фиксируем время начала подбора
                if (fPtrNewConnection == nullptr) {
                    fPtrNewConnection.reset(new TConnectionServer (commonDefine::portNumber));   // Пока порт на потором висит сервер поменять нельзя
                    makeConnectServer () ;


                    setServerState(TConnection::stStart) ;

                }
                  else throw exception::errServerSecondInstance ;   // Летим по ошибке, т.к. подбор уже запущен. Как такое может произойти не совсем понятно.
            break ;


            case TConnection::stStart :
                setServerState(TConnection::stPause) ;
                setElementFormVisible () ;
            break ;

            case TConnection::stPause :
                setServerState(TConnection::stStart) ;
                setElementFormVisible () ;
            break ;

            default :
                setServerState(TConnection::stUnknown) ;         // Если мы сюда попали, то кнопка btnRun активна в каком-то не понятном состоянии. Тупо прекратить выполнение assert'ом мы не можем, т.к. могут быть активны соединения
                throw exception::errServerUnknownState ;
            break ;
        }
    }
      catch (exception::TException& ex) {
        QMessageBox::critical(this, QString::fromStdString(exception::criticalError), QString::fromStdString(ex.what()), QMessageBox::Ok) ;
      }

      catch (...) {
        QMessageBox::critical(this, QString::fromStdString(exception::criticalError), "Ошибка при запуске подбора", QMessageBox::Ok) ;
      }
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
    setElementFormVisible () ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceServer::on_spThreadCount_textChanged Слот для проверки заполненности поля spThreadCount
 * \param inThreadCount Проверяемое значение
 */
void prS63BruteForceServer::on_spThreadCount_textChanged(const QString &inThreadCount)
{
    if (inThreadCount.isEmpty()) fReadyToStart.reset(bitBlockSize) ;
      else fReadyToStart.set(bitBlockSize) ;
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
    setElementFormVisible () ;
}
//-----------------------------------------------------------------------------

