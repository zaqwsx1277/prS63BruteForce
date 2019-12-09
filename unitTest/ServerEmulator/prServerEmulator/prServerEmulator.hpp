#ifndef PRSERVEREMULATOR_HPP
#define PRSERVEREMULATOR_HPP

#include <QMainWindow>
#include <QTcpServer>

#include <memory>
#include <thread>
#include <set>

#include "TSEConnection.hpp"
#include "TSEmodel.hpp"
#include "TCommonDefaneServer.hpp"

using namespace connection ;
using namespace server ;

namespace Ui {
class prServerEmulator;
}

//-----------------------------------------------------
/*!
 * \brief Эмулятор работы сервера предназначеный для отладки Клиентской части. Порт по которому принимаются входящие соединения 9993
 */
class prServerEmulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit prServerEmulator(QWidget *parent = 0);
    ~prServerEmulator();

private:

    bool threadIdComp = [] (commonDefineServer::tdPtrClientDescr left, commonDefineServer::tdPtrClientDescr right) { return (left -> threadId < right -> threadId ) ; } ;
    std::set <commonDefineServer::tdPtrClientDescr, decltype (threadIdComp)> fConnectionList ; ///< список соединений которые обрабатывает сервер

    Ui::prServerEmulator *ui;

    QHostAddress fHostAddress ;     // Адрес подключившегося клиента
    std::unique_ptr <connection::TSEConnection> fPtrConnection  {nullptr} ; // Указатель на класс обрабатывающий всю работу по сети.
    std::unique_ptr <TSEmodel> fPrtSEModel {nullptr} ;  // Указатель на модель отображения лога

    void setConnect () ;            // Формирование всех конектов
    void clear () ;                 // Очистка всех полей

    void closeEvent (QCloseEvent*) ; // Событие срабатывающее на закрытие формы

private slots:
    void slotHostConnected () ;  // Слот срабатывающий при подключении клиента
    void slotHostDisconnected (quint32) ; // Слот срабатывающий при отключении клиента
    void slotHostError (quint32, QAbstractSocket::SocketError) ; // Слот срабатывающий при ошибки от клиента

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // PRSERVEREMULATOR_HPP
