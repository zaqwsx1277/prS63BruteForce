#ifndef PRS63BRUTEFORCESERVER_HPP
#define PRS63BRUTEFORCESERVER_HPP

#include <QMainWindow>

namespace Ui {
class prS63BruteForceServer;
}

class prS63BruteForceServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit prS63BruteForceServer(QWidget *parent = 0);
    ~prS63BruteForceServer();

private:
    Ui::prS63BruteForceServer *ui;
};

#endif // PRS63BRUTEFORCESERVER_HPP
