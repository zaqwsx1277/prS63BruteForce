#ifndef PRHACKS63MAINWINDOW_H
#define PRHACKS63MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include <memory>
#include <chrono>
#include <map>
#include <bitset>

#include "TCommonDefaneServer.hpp"
#include "TConnectionServer.hpp"
#include "TBruteForceManager.hpp"

namespace Ui {
class prS63BruteForceServer;
}

namespace server {

class prS63BruteForceServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit prS63BruteForceServer(QWidget *parent = nullptr);
    ~prS63BruteForceServer();

private slots:
    void on_btnRun_clicked();       // Слот обрабатывающий запуск подбора
    void on_spPathFrom_textChanged(const QString &arg1);
    void on_spThreadCount_textChanged(const QString &arg1);
    void on_spKeyStart_textChanged(const QString &arg1);
    void on_spKeyStop_textChanged(const QString &arg1);

private:
    Ui::prS63BruteForceServer *ui;


    enum bitPos {bitPathFrom = 0,    /// bit 0 - заполненность поля spPathFrom
                 bitThreadCount = 1, /// bit 1 - заполненность поля spThreadCount
                 bitKeyStart = 2,    /// bit 2 - заполненность поля spKeyStart
                 bitKeyStop = 3,     /// bit 3 = заполненность поля spKeyStop
                 bitCount} ;
    std::bitset <bitPos::bitCount> fReadyToStart ; // Битовое значение для контроля готовности всех данных для запуска подбора. Позиции битов определяются в bitPos

    std::unique_ptr <TBruteForceManager> fPtrBruteForceManager { new TBruteForceManager ()} ; // Указатель на менеджер распределения блоков и обработки полученных данных
//    std::map <quint64, commonDefineServer::brutForceItem> fListItems ;   // Контейнер содержащий все блоки для обработки
//    std::unique_ptr <connection::TConnectionServer> fPtrConnectionServer { new connection::TConnectionServer ()} ; // Указатель на класс обрабатывающий соединения в распеделенной системе

    void initForm () ;              // инициализация формы
    void setElementFormVisible () ; // Увтановка видимости элементов в зависимсоти от состояния
    void makeConnect () ;           // Формирует все нужные конекты
    bool checkReadyToStart () ;     // Проверка заполненности всех полей

    void timerEvent(QTimerEvent*) ; // таймер обновляющий модель

    std::chrono::time_point<std::chrono::system_clock> fTimeStart ; // Время начала выполнения задания

    void closeEvent(QCloseEvent *event) ; // Событие для проверки возможности закрытия приложения
};

}
#endif // PRHACKS63MAINWINDOW_H
