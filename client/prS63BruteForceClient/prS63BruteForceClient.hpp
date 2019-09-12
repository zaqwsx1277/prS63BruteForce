#ifndef PRS63BRUTEFORCECLIENT_HPP
#define PRS63BRUTEFORCECLIENT_HPP

#include <QMainWindow>

namespace Ui {
class prS63BruteForceClient;
}

class prS63BruteForceClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit prS63BruteForceClient(QWidget *parent = 0);
    ~prS63BruteForceClient();

private:
    Ui::prS63BruteForceClient *ui;
};

#endif // PRS63BRUTEFORCECLIENT_HPP
