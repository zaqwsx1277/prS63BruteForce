#include "prS63BruteForceClient.hpp"
#include "ui_prS63BruteForceClient.h"

#include "TCommonDefine.hpp"
#include "TCommonDefaneClient.hpp"

#include <thread>

#include <QAbstractItemModel>
#include <QMessageBox>

using namespace client ;
//---------------------------------------------------------------------
prS63BruteForceClient::prS63BruteForceClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceClient)
{
    ui->setupUi(this);

    fPtrConnectionClient.reset(new connection::TConnectionClient ()) ;  // инициализируем работу с сервером
    initForm () ;
    clearForm () ;
    startTimer(commonDefineClient::timerRefresh) ;          // Запускаем таймер на обновление формы
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
                                    // задаём все необходимые регулярные выражения
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    ui -> spServerAddress -> setValidator( new QRegExpValidator( QRegExp( "^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$")));
    ui -> spServerPort -> setValidator( new QRegExpValidator( QRegExp( "([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])")));
    ui -> spThreadCount -> setValidator( new QRegExpValidator( QRegExp(ipRange))) ; // можно установить не более 255 потоков
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::clearForm  Очищаем и устанавливаем начальные значения всех элементов формы
 */
void prS63BruteForceClient::clearForm ()
{
    ui -> spServerAddress -> setText (fPtrConnectionClient -> getIpAddressServer().toString())  ;
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
    fPtrConnectionClient -> seachServer(ui ->spServerPort->text().toUShort());
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::timerEvent Обработчик таймера для обновления формы
 * \param event
 */
void prS63BruteForceClient::timerEvent(QTimerEvent *event)
{
    showState () ;
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::showState  Вывод текущего состояния клиента
 */
void prS63BruteForceClient::showState ()
{
    switch (fPtrConnectionClient -> getState()) {
      case connection::TConnectionClient::stUnknown:
      default:
        ui -> spState -> setText(commonDefineClient::stateUnknown);
      break;

      case connection::TConnectionClient::stError :
        ui -> spState -> setText(commonDefineClient::stateError);
      break;

      case connection::TConnectionClient::stWait :
        ui -> spState -> setText(commonDefineClient::stateWait);
      break;

      case connection::TConnectionClient::stStart :
        ui -> spState -> setText(commonDefineClient::stateStart);
      break;

      case connection::TConnectionClient::stStop :
        ui -> spState -> setText(commonDefineClient::stateStop);
      break;

      case connection::TConnectionClient::stServerSearch :
        ui -> spState -> setText(commonDefineClient::stateServerSearch);
      break;

      case connection::TConnectionClient::stPause :
        ui -> spState -> setText(commonDefineClient::statePause);
      break;
    }
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::on_btnStart_clicked    Слот запускающий подбор пароля
 */
void prS63BruteForceClient::on_btnStart_clicked()
{
    if (fPrtClientModel.get() != nullptr) disconnect (ui -> spLog -> model(), &QAbstractItemModel::rowsInserted, ui -> spLog, &QTableView::scrollToBottom) ;
    fPrtClientModel.reset( new client::TClientModel (ui -> spThreadCount -> text().toUShort()));
    ui -> spLog -> setModel(fPrtClientModel.get()) ;                             // Инициализируем таблицу для ведения лога
    for (quint8 i = 0; i < fPrtClientModel -> columnCount (); i++) {
        ui-> spLog -> horizontalHeader() -> setSectionResizeMode(i, QHeaderView::Stretch) ;
    }
    connect(ui -> spLog -> model(), &QAbstractItemModel::rowsInserted, ui -> spLog, &QTableView::scrollToBottom) ;    // Устанавливаем текущей последнюю строку
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
