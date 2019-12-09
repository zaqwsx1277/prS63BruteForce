#ifndef PRHACKS63MAINWINDOW_H
#define PRHACKS63MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include <memory>
#include <chrono>
#include <map>
#include <queue>
#include <bitset>

#include "TCommonDefaneServer.hpp"
#include "TConnectionServer.hpp"
#include "TBruteForceManager.hpp"
#include "TServerLogModel.h"
#include "TServerKeyModel.h"

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

    void slotHostConnected (QTcpSocket *) ;   ///< Слот срабатывающий при подключении клиента
//    void slotHostDisconnected (quint32) ; // Слот срабатывающий при отключении клиента
//    void slotHostError (quint32, QAbstractSocket::SocketError) ; // Слот срабатывающий при ошибки от клиента

private:
    Ui::prS63BruteForceServer *ui;
                                     /// Номера позиций битов для проверки заполненности всех полей
    enum bitPos {bitPathFrom = 0,    ///< bit 0 - заполненность поля spPathFrom
                 bitThreadCount = 1, ///< bit 1 - заполненность поля spThreadCount
                 bitKeyStart = 2,    ///< bit 2 - заполненность поля spKeyStart
                 bitKeyStop = 3,     ///> bit 3 = заполненность поля spKeyStop
                 bitCount} ;
    std::bitset <bitPos::bitCount> fReadyToStart ; // Битовое значение для контроля готовности всех данных для запуска подбора. Позиции битов определяются в bitPos
    std::unique_ptr <TServerLogModel> fPrtLogModel {nullptr} ;  // Указатель на модель отображения лога
    std::unique_ptr <TServerKeyModel> fPrtKeyModel {nullptr} ;  // Указатель на модель отображения лога

//    std::unique_ptr <TBruteForceManager> fPtrBruteForceManager { new TBruteForceManager ()} ; // Указатель на менеджер распределения блоков и обработки полученных данных
//    std::map <quint64, commonDefineServer::brutForceItem> fListItems ;   // Контейнер содержащий все блоки для обработки
    std::unique_ptr <connection::TConnectionServer> fPtrConnectionServer { new connection::TConnectionServer ()} ; // Указатель на класс обрабатывающий входящие соединения в распеделенной системе
    std::queue <commonDefineServer::tdClientDescr> fConnectionQueue ;      // контейнер для обработки входящих соединений менеджером обработки подключений

    void initForm () ;              // инициализация формы
    void setElementFormVisible () ; // Увтановка видимости элементов в зависимсоти от состояния
    void makeConnect () ;           // Формирует все нужные конекты
    bool checkReadyToStart () ;     // Проверка заполненности всех полей
    void setServerConnect () ;      // Инициализация всех connect'ов при запуске сервера

    void connectionManager () ;     // Менеджер обработки входящих соединений

    void timerEvent(QTimerEvent*) ; // таймер обновляющий модель

    std::chrono::time_point<std::chrono::system_clock> fTimeStart ; // Время начала выполнения задания

    void closeEvent(QCloseEvent *event) ; // Событие для проверки возможности закрытия приложения
};

}
#endif // PRHACKS63MAINWINDOW_H
