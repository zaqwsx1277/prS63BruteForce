#ifndef PRSERVEREMULATOR_HPP
#define PRSERVEREMULATOR_HPP

#include <QMainWindow>
#include <QTcpServer>

#include <memory>

#include "TSEConnection.hpp"
#include "TSEmodel.hpp"

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
    Ui::prServerEmulator *ui;

    QHostAddress fHostAddress ;     // Адрес подключившегося клиента
    std::unique_ptr <connection::TSEConnection> fPtrConnection  {nullptr} ; // Указатель на класс обрабатывающий всю работу по сети.
    std::unique_ptr <TSEmodel> fPrtSEModel {nullptr} ;  // Указатель на модель отображения лога

    void setConnect () ;            // Формирование всех конектов
    void clear () ;                 // Очистка всех полей

private slots:
    void slotHostConnected (quint32) ;  // Слот срабатывающий при подключении клиента
    void slotHostDisconnected (quint32) ; // Слот срабатывающий при отключении клиента
    void slotHostError (quint32, QAbstractSocket::SocketError) ; // Слот срабатывающий при ошибки от клиента

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // PRSERVEREMULATOR_HPP
