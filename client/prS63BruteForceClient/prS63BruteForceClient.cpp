#include "prS63BruteForceClient.hpp"
#include "ui_prS63BruteForceClient.h"

#include "TCommonDefine.hpp"
#include "TCommonDefaneClient.hpp"

#include <thread>

//---------------------------------------------------------------------
prS63BruteForceClient::prS63BruteForceClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceClient)
{
    ui->setupUi(this);

    fPtrConnectionClient.reset(new TConnectionClient ()) ;  // инициализируем работу с сервером
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
      case TConnectionClient::stUnknown:
      default:
        ui -> spState -> setText(commonDefineClient::stateUnknown);
      break;

      case TConnectionClient::stError :
        ui -> spState -> setText(commonDefineClient::stateError);
      break;

      case TConnectionClient::stWait :
        ui -> spState -> setText(commonDefineClient::stateWait);
      break;

      case TConnectionClient::stStart :
        ui -> spState -> setText(commonDefineClient::stateStart);
      break;

      case TConnectionClient::stStop :
        ui -> spState -> setText(commonDefineClient::stateStop);
      break;

      case TConnectionClient::stServerSearch :
        ui -> spState -> setText(commonDefineClient::stateServerSearch);
      break;

      case TConnectionClient::stPause :
        ui -> spState -> setText(commonDefineClient::statePause);
      break;
    }
}
//----------------------------------------------------------------------
