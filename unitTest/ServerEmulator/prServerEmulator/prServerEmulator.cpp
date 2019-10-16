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
 * \brief clear Очистка всех полей
 */
void prServerEmulator::clear ()
{
    ui -> spClientAddress -> clear();
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
