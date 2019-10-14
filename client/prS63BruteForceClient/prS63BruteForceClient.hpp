#ifndef PRS63BRUTEFORCECLIENT_HPP
#define PRS63BRUTEFORCECLIENT_HPP

#include <QMainWindow>

#include <memory>
#include <bitset>

#include "TConnectionClient.hpp"
#include "TClientModel.hpp"

namespace Ui {
class prS63BruteForceClient;
}

namespace client {
/*!
 * \brief Форма главного окна клиента для подбора пароля.
 *
 * Описание работы клиента находится в файле readme.md
 */
class prS63BruteForceClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit prS63BruteForceClient(QWidget *parent = 0);
    ~prS63BruteForceClient();

private slots:
    void on_btnSeachServer_clicked();
    void on_btnStart_clicked();
    void on_spServerAddress_textChanged(const QString &arg1);
    void on_spServerPort_textChanged(const QString &arg1);
    void on_spThreadCount_textChanged(const QString &arg1);

private:
    Ui::prS63BruteForceClient *ui;

    enum bitPos {bitServerAddress = 0,  // bit 0 - заполненность поля spServerAddress
                 bitServerPort = 1,     // bit 1 - заполненность поля spServerPort
                 bitThreadCount = 2,    // bit 3 = заполненность поля spThreadCount
                 count} ;
    std::bitset <bitPos::count> fReadyToStart {std::string ("000")} ; // Битовое значение для контроля готовности всех данных для запуска подбора. Позиции битов определяются в bitPos

    std::shared_ptr <connection::TConnectionClient> fPtrConnectionClient {nullptr}; // Указатель на класс обрабатывающий подключение к серверу
    std::unique_ptr <client::TClientModel> fPrtClientModel {nullptr} ;          // Указатель на модель вывода лога

    void initForm () ;          // инициализирую все элементы формы
    void clearForm () ;         // Очищаем и устанавливаем начальные значения всех элементов формы
    void setElementFormVisible () ; // Установка видимости элементов в зависимсоти от состояния
    void showState () ;         // Вывод состояния

    void timerEvent(QTimerEvent *event) ;   // Обработчик таймера для обновления формы
};

}
#endif // PRS63BRUTEFORCECLIENT_HPP
