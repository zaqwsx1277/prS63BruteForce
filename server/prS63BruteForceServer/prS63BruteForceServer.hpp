#ifndef PRHACKS63MAINWINDOW_H
#define PRHACKS63MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <chrono>
#include <map>
#include <bitset>

#include "TCommonDefaneServer.hpp"
#include "TConnectionServer.hpp"

namespace Ui {
class prS63BruteForceServer;
}

class prS63BruteForceServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit prS63BruteForceServer(QWidget *parent = 0);
    ~prS63BruteForceServer();

private slots:
    void on_btnRun_clicked();       // Слот обрабатывающий запуск подбора

    void on_spPathFrom_textChanged(const QString &arg1);

private:
    Ui::prS63BruteForceServer *ui;

    std::bitset <4> fReadyToStart ; // Битовое значение для контроля готовности всех данных для запуска подбора
                                    // bit 0 - заполненность поля spPathFrom
                                    // bit 1 - заполненность поля spThreadCount
                                    // bit 2 - заполненность поля spKeyStart
                                    // bit 3 = заполненность поля spKeyStop

    std::map <quint64, commonDefineServer::brutForceItem> fListItems ;   // Контейнер содержащий все блоки для обработки
    std::unique_ptr <TConnectionServer> fPtrConnectionServer { new TConnectionServer ()} ; // Указатель на класс обрабатывающий соединения в распеделенной системе

    void initForm () ;              // инициализация формы
    void makeConnect () ;           // Формирует все нужные конекты
    bool checkReadyToStart () ;     // Проверка заполненности всех полей

    void timerEvent(QTimerEvent*) ; // таймер обновляющий модель

    std::chrono::time_point<std::chrono::system_clock> fTimeStart ; // Время начала выполнения задания

    bool serverStart () ;           // Запуск сервера для распределенной работы
    bool serverStop () ;            // Останов сервера
    bool serverPause () ;           // Приостановка работы сервера

    bool bruteForceManagerStart () ;// Запуск менеджера распределения ключей
    bool bruteForceManagerStop () ; // Останов менеджера
    bool bruteForceManagerPause () ; // Останов менеджера
};

#endif // PRHACKS63MAINWINDOW_H
