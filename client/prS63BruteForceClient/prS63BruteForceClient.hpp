#ifndef PRS63BRUTEFORCECLIENT_HPP
#define PRS63BRUTEFORCECLIENT_HPP

#include <QMainWindow>

#include <memory>

#include "TConnectionClient.hpp"
#include "TClientModel.hpp"

namespace Ui {
class prS63BruteForceClient;
}

class prS63BruteForceClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit prS63BruteForceClient(QWidget *parent = 0);
    ~prS63BruteForceClient();

private slots:
    void on_btnSeachServer_clicked();

    void on_btnStart_clicked();

private:
    Ui::prS63BruteForceClient *ui;

    std::shared_ptr <TConnectionClient> fPtrConnectionClient {nullptr}; // Указатель на класс обрабатывающий подключение к серверу
    std::unique_ptr <client::TClientModel> fPrtClientModel {nullptr} ;          // Указатель на модель вывода лога

    void initForm () ;          // инициализирую все элементы формы
    void clearForm () ;         // Очищаем и устанавливаем начальные значения всех элементов формы
    void showState () ;         // Вывод состояния

    void timerEvent(QTimerEvent *event) ;   // Обработчик таймера для обновления формы
};

#endif // PRS63BRUTEFORCECLIENT_HPP
