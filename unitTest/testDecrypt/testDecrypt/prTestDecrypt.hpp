#ifndef PRTESTDECRYPT_HPP
#define PRTESTDECRYPT_HPP

#include <QMainWindow>

namespace Ui {
class prTestDecrypt;
}

namespace unitTest {

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
};

}

#endif // PRTESTDECRYPT_HPP
