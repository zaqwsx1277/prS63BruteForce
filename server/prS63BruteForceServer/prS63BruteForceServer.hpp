#ifndef PRHACKS63MAINWINDOW_H
#define PRHACKS63MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <chrono>

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

private:
    Ui::prS63BruteForceServer *ui;

    void initForm () ;              // инициализация формы
    void makeConnect () ;           // Формирует все нужные конекты

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
