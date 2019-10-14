#ifndef PRSERVEREMULATOR_HPP
#define PRSERVEREMULATOR_HPP

#include <QMainWindow>
#include <QTcpServer>

#include <memory>

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

    std::unique_ptr <QTcpServer> fPtrServer {new QTcpServer ()} ;

private slots:
    void slotHostConnected () ; // Слот срабатывающий при подключении клиента

};

#endif // PRSERVEREMULATOR_HPP
