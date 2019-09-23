#ifndef PRHACKS63MAINWINDOW_H
#define PRHACKS63MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <chrono>

namespace Ui {
class prHackS63MainWindow;
}

class prHackS63MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit prHackS63MainWindow(QWidget *parent = 0);
    ~prHackS63MainWindow();

private slots:
    void on_btnRun_clicked();       // Слот обрабатывающий запуск подбора

private:
    Ui::prHackS63MainWindow *ui;

    void initForm () ;              // инициализация формы
    void makeConnect () ;           // Формирует все нужные конекты

    void timerEvent(QTimerEvent*) ; // таймер обновляющий модель

    std::chrono::time_point<std::chrono::system_clock> fTimeStart ; // Время начала выполнения задания
};

#endif // PRHACKS63MAINWINDOW_H
