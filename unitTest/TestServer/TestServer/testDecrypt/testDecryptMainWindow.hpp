#ifndef TESTDECRYPTMAINWINDOW_HPP
#define TESTDECRYPTMAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class testDecryptMainWindow;
}

namespace unitTest {

class testDecryptMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit testDecryptMainWindow(QWidget *parent = 0);
    ~testDecryptMainWindow();

private:
    Ui::testDecryptMainWindow *ui;
};

}
#endif // TESTDECRYPTMAINWINDOW_HPP
