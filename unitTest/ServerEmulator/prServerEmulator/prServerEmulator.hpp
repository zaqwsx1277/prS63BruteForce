#ifndef PRSERVEREMULATOR_HPP
#define PRSERVEREMULATOR_HPP

#include <QMainWindow>
#include <QTcpServer>

#include <memory>

#include "TSEConnection.hpp"

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
    std::unique_ptr <connection::TSEConnection> fPtrConnection  {nullptr} ; // Указатель на класс обрабатывающий всю работу по сети

    void setConnect () ;            // Формирование всех конектов
    void clear () ;                 // Очистка всех полей

private slots:
    void slotHostConnected (quint32) ;  // Слот срабатывающий при подключении клиента
    void on_pushButton_clicked();
};

#endif // PRSERVEREMULATOR_HPP
