#include "prServerEmulator.hpp"
#include "ui_prServerEmulator.h"

#include <QTcpSocket>

//-----------------------------------------------------------------------------
prServerEmulator::prServerEmulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prServerEmulator)
{
    ui->setupUi(this);

    clear() ;

    fPrtSEModel.reset( new TSEmodel ());
    ui -> spLog -> setModel(fPrtSEModel.get()) ;
    for (quint8 i = 0; i < fPrtSEModel -> columnCount (); i++) {
        ui-> spLog -> horizontalHeader() -> setSectionResizeMode(i, QHeaderView::Stretch) ;
    }
    connect(ui -> spLog -> model(), &QAbstractItemModel::rowsInserted, ui -> spLog, &QTableView::scrollToBottom) ;    // Устанавливаем текущей последнюю строку

    fPtrConnection.reset(new connection::TSEConnection) ;
    setConnect () ;
}
//------------------------------------------------------------------------------
prServerEmulator::~prServerEmulator()
{
    delete ui;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prServerEmulator::setConnect  Формирование всех конектов
 */
void prServerEmulator::setConnect ()
{
    connect (fPtrConnection.get(), &connection::TSEConnection::signalHostConnected, this, &prServerEmulator::slotHostConnected) ;
    connect (fPtrConnection.get(), &connection::TSEConnection::signalHostDisconnected, this, &prServerEmulator::slotHostDisconnected ) ;

}
//-----------------------------------------------------------------------------
/*!
 * \brief prServerEmulator::slotHostConnected  Слот срабатывающий при подключении клиента
 */
void prServerEmulator::slotHostConnected (quint32 inHostAddress)
{
    fHostAddress = QHostAddress (inHostAddress) ;
    ui -> spClientAddress ->setText(fHostAddress.toString());
}
//-----------------------------------------------------------------------------
/*!
 * \brief prServerEmulator::slotHostDisconnected  Слот срабатывающий при отключении клиента
 */
void prServerEmulator::slotHostDisconnected (quint32 inHostAddress)
{
    fHostAddress = QHostAddress () ;
    clear () ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prServerEmulator::slotHostError Слот срабатывающий при ошибки от клиента
 */
void prServerEmulator::slotHostError (quint32 inHostAddress, QAbstractSocket::SocketError inError)
{

}
//-----------------------------------------------------------------------------
/*!
 * \brief clear Очистка всех полей
 */
void prServerEmulator::clear ()
{
    ui -> spClientAddress -> clear() ;
    ui -> spClientState -> clear() ;
}
//-----------------------------------------------------------------------------
/*!
 * \brief prServerEmulator::on_pushButton_clicked   Слот реагирующий на нажатие кнопки закрытия соединения с клиентом
 */
void prServerEmulator::on_pushButton_clicked()
{
    fPtrConnection -> connectionClose();
    clear () ;
}
//-----------------------------------------------------------------------------
