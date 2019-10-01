#ifndef PRTESTDECRYPT_HPP
#define PRTESTDECRYPT_HPP

#include <QMainWindow>

#include "TTestDecryptLogModel.hpp"


namespace Ui {
class prTestDecrypt;
}

namespace unitTest {
//---------------------------------------------------------------------------
/*!
 * \brief Unit Test для отработки библиотечных функций декодирования и разархивации файла S63 в S57
 */
class prTestDecrypt : public QMainWindow
{
    Q_OBJECT

public:
    explicit prTestDecrypt(QWidget *parent = 0);
    ~prTestDecrypt();

private slots:
    void on_btnPathFrom_clicked();
    void on_btnPathTo_clicked();

    void on_btnConvert_clicked();

private:
    Ui::prTestDecrypt *ui;

    std::unique_ptr <TTestDecryptLogModel> fPrtLogModel {nullptr} ; // Указатель на модель для отображения лога работы юнит теста
};

}

#endif // PRTESTDECRYPT_HPP
