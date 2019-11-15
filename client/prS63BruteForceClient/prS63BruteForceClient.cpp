#include "prS63BruteForceClient.hpp"
#include "ui_prS63BruteForceClient.h"

#include "TCommonDefine.hpp"
#include "TCommonDefaneClient.hpp"

#include <thread>
#include <memory>

#include <QAbstractItemModel>
#include <QMessageBox>
#include <QHostAddress>

using namespace client ;
//---------------------------------------------------------------------
prS63BruteForceClient::prS63BruteForceClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceClient)
{
    ui->setupUi(this);

    initForm () ;
    clearForm () ;
    fPtrConnectionClient.reset(new TConnectionClient ()) ;  // инициализируем работу с сервером
    fTimerIdRefresh = startTimer(commonDefineClient::timerRefresh) ;  // Запускаем таймер на обновление формы

    makeSlotConnection () ;
    fPtrConnectionClient -> seachServer(commonDefine::portNumber);
}
//----------------------------------------------------------------------
prS63BruteForceClient::~prS63BruteForceClient()
{
    delete ui;
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::initForm   инициализирую все элементы формы
 */
void prS63BruteForceClient::initForm ()
{
                                    // Инициализируем таблицу для ведения лога
    if (fPrtClientModel) disconnect (ui -> spLog -> model(), &QAbstractItemModel::rowsInserted, ui -> spLog, &QTableView::scrollToBottom) ;
    fPrtClientModel.reset( new client::TClientModel (ui -> spThreadCount -> text().toUShort()));
    ui -> spLog -> setModel(fPrtClientModel.get()) ;
    for (quint8 i = 0; i < fPrtClientModel -> columnCount (); i++) {
        ui-> spLog -> horizontalHeader() -> setSectionResizeMode(i, QHeaderView::Stretch) ;
    }
    connect(ui -> spLog -> model(), &QAbstractItemModel::rowsInserted, ui -> spLog, &QTableView::scrollToBottom) ;    // Устанавливаем текущей последнюю строку

                                    // задаём все необходимые регулярные выражения
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    ui -> spServerAddress -> setValidator( new QRegExpValidator( QRegExp( "^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$")));
    ui -> spServerPort -> setValidator( new QRegExpValidator( QRegExp( "([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])")));
    ui -> spThreadCount -> setValidator( new QRegExpValidator( QRegExp(ipRange))) ; // можно установить не более 255 потоков
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::makeSlotConnection Подключение всех необходимых слотов для работы с сервером
 */
void prS63BruteForceClient::makeSlotConnection ()
{
    fPtrStateRefresh.reset(new QTimer ()) ;                 // Инициализация таймера на запрос состояния сервера
    connect (fPtrStateRefresh.get (), &QTimer::timeout, this, &prS63BruteForceClient::slotStateRefresh) ;

    if (fPtrConnectionClient) {                             // Инициализация всех конектов
        connect(fPtrConnectionClient.get(), &TConnectionClient::signalHostConnected, this, &prS63BruteForceClient::slotHostConnected) ;
        connect(fPtrConnectionClient.get(), &TConnectionClient::signalHostDisconnected, this, &prS63BruteForceClient::slotHostDisconnected) ;
        connect(fPtrConnectionClient.get(), &TConnectionClient::signalReadData, this, &prS63BruteForceClient::slotReadData) ;
    }
    else {

    }

}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::clearForm  Очищаем и устанавливаем начальные значения всех элементов формы
 */
void prS63BruteForceClient::clearForm ()
{
    ui -> spServerAddress -> setText (fPtrConnectionClient ? fPtrConnectionClient -> getIpAddressServer().toString(): "")  ;
    ui -> spServerPort -> setText (QString::number(commonDefine::portNumber)) ;
    ui -> spBlockSize -> clear() ;
    ui -> spThreadCount -> setText(QString::number(std::thread::hardware_concurrency()));
    ui -> spState -> clear();
                                    // Установка всех битовых флагов заполненности полей
    fReadyToStart.set () ;
    if (ui -> spServerAddress -> text().isEmpty()) fReadyToStart.reset(bitServerAddress) ;
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::on_btnSeachServer_clicked  Слот поиска сервера в локальной сети
 */
void prS63BruteForceClient::on_btnSeachServer_clicked()
{
    fPtrConnectionClient -> seachServer(ui -> spServerPort -> text().toUShort());
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::timerEvent Обработчик таймера для обновления формы
 * \param event
 */
void prS63BruteForceClient::timerEvent(QTimerEvent *event)
{
    showState () ;
    refreshLog () ;
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::showState  Вывод текущего состояния клиента
 */
void prS63BruteForceClient::showState ()
{
    if (fPtrConnectionClient) {
        switch (fPtrConnectionClient -> getState()) {
          case connection::TConnection::stUnknown:
          default:
            ui -> spState -> setText(commonDefineClient::stateUnknown);
          break;

          case connection::TConnection::stError :
            ui -> spState -> setText(commonDefineClient::stateError);
          break;

          case connection::TConnection::stWait :
            ui -> spState -> setText(commonDefineClient::stateWait);
          break;

          case connection::TConnection::stStart :
            ui -> spState -> setText(commonDefineClient::stateStart);
          break;

          case connection::TConnection::stStop :
            ui -> spState -> setText(commonDefineClient::stateStop);
          break;

          case connection::TConnection::stServerSearch :
            ui -> spState -> setText(commonDefineClient::stateServerSearch);
          break;

          case connection::TConnection::stPause :
            ui -> spState -> setText(commonDefineClient::statePause);
          break;

          case connection::TConnection::stConnected :
            ui -> spState -> setText(commonDefineClient::stateConnectedToServer);
          break;

          case connection::TConnection::stDisconnected :
            ui -> spState -> setText(commonDefineClient::stateDisconnectedFromServer);
          break;
        }
    }
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::on_btnStart_clicked    Слот запускающий подбор пароля
 */
void prS63BruteForceClient::on_btnStart_clicked()
{

}
//--------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::setElementFormVisible  Установка видимости элементов в зависимсоти от состояния
 */
void prS63BruteForceClient::setElementFormVisible ()
{
    if (fReadyToStart.all()) {

    }
}
//--------------------------------------------------------------------------
void client::prS63BruteForceClient::on_spServerAddress_textChanged(const QString &inServerAddress)
{
    if (inServerAddress.isEmpty()) fReadyToStart.reset(bitServerAddress) ;
      else fReadyToStart.set(bitServerAddress) ;
    setElementFormVisible () ;
}
//--------------------------------------------------------------------------

void client::prS63BruteForceClient::on_spServerPort_textChanged(const QString &inServerPort)
{
    if (inServerPort.isEmpty()) fReadyToStart.reset(bitServerPort) ;
      else fReadyToStart.set(bitServerPort) ;
    setElementFormVisible () ;
}
//--------------------------------------------------------------------------

void client::prS63BruteForceClient::on_spThreadCount_textChanged(const QString &inThreadCount)
{
    if (inThreadCount.isEmpty()) fReadyToStart.reset(bitServerPort) ;
      else {
        fReadyToStart.set(bitServerPort) ;
        if (inThreadCount.toInt() > std::thread::hardware_concurrency()) {
          if (QMessageBox::warning(this, "Внимание","Количество введённых потоков превышает\nих реальное количество", QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Cancel)
            ui -> spThreadCount -> setText(QString::number(std::thread::hardware_concurrency()));
        }
      }
    setElementFormVisible () ;
}
//--------------------------------------------------------------------------
/*!
 * \brief client::prS63BruteForceClient::slotStateRefresh Слот обрабатывающий таймер на обновление статуса сервера
 */
void client::prS63BruteForceClient::slotStateRefresh ()
{

}
//--------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::slotHostConnected  Слот обрабатывающий подключение клиента к серверу
 */
void prS63BruteForceClient::slotHostConnected (QHostAddress inHostConnected)
{
    if (fPrtClientModel) {
        fPtrConnectionClient -> setState(TConnection::stConnected);
                                // Записываем в лог информацию о подключении к серверу
        commonDefineClient::tdLogItemClient item = std::make_shared <commonDefineClient::TLogItemClient> () ;
        item -> comment = commonDefineClient::logServerConnected + inHostConnected.toString() ;
        ui -> spServerAddress -> setText(inHostConnected.toString()) ;
        fPrtClientModel -> push_back(item);
    }
}
//--------------------------------------------------------------------------
/*!
 * \brief prExampleMainWindow::refreshLog   Обновление отображения данных
 * Т.К. подбор ведется в несколько потоков, то на момент обновления отображения блокируется доступ к контейнеру с данными лога
 */
void prS63BruteForceClient::refreshLog ()
{
    if (fPrtClientModel && fPtrConnectionClient -> getState() != TConnection::stAppClose) {
        std::lock_guard <std::mutex> refreshWait (commonDefine::mutexRefresh) ; // блокируем допуск остальным потокaм на работу с контейнером
        fPrtClientModel -> refreshView() ;                                      // Обновляем отображение данных
        QApplication::processEvents() ;
    }
}
//---------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::slotHostDisconnected Слот обрабатывающий отключение от сервера
 */
void prS63BruteForceClient::slotHostDisconnected ()
{
    if (fPtrConnectionClient -> getState() != TConnection::stAppClose) {
        fPtrConnectionClient -> setState(TConnection::stDisconnected);
                                // Записываем в лог информацию об отключении от сервера
        commonDefineClient::tdLogItemClient item = std::make_shared <commonDefineClient::TLogItemClient> () ;
        item -> comment = commonDefineClient::logServerDisconnected + fPtrConnectionClient -> getIpAddressServer().toString() ;
        ui -> spServerAddress -> clear() ;
        fPrtClientModel -> push_back(item);
    }
}
//---------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::slotReadData   Слот обрабатывающий получение данных от сервера
 */
void prS63BruteForceClient::slotReadData (TDataTransfer inDataTransfer)
{
    switch (inDataTransfer.command) {
      case TConnection::cmdStateRequest : {
        commonDefineClient::tdLogItemClient item = std::make_shared <commonDefineClient::TLogItemClient> () ;
        item -> comment = commonDefineClient::logServerStateRequest ;
        fPrtClientModel -> push_back(item);

        TDataTransfer dataTransfer ;// Автоматически возвращаем серверу состояние клиента
        dataTransfer.command = TConnection::cmdStateConfirm ;
        dataTransfer.data = fPtrConnectionClient -> getState() ;
        fPtrConnectionClient -> sendData (dataTransfer) ;

      }
      break ;

      default :
      break ;
    }
}
//---------------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::closeEvent     Обработчик события на закрытие формы
 * \param inEvent
 */
void prS63BruteForceClient::closeEvent(QCloseEvent* inEvent)
{
    fPtrConnectionClient -> setState(TConnection::stAppClose) ;
    killTimer(fTimerIdRefresh);     // Останавливаем запущенные таймеры
}
//---------------------------------------------------------------------------
