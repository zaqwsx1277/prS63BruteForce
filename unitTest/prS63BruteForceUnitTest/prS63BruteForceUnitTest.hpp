#ifndef PRS63BRUTEFORCEUNITTEST_HPP
#define PRS63BRUTEFORCEUNITTEST_HPP

#include <QMainWindow>

namespace Ui {
class prS63BruteForceUnitTest;
}

class prS63BruteForceUnitTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit prS63BruteForceUnitTest(QWidget *parent = 0);
    ~prS63BruteForceUnitTest();

private:
    Ui::prS63BruteForceUnitTest *ui;
};

#endif // PRS63BRUTEFORCEUNITTEST_HPP
