#include "prS63BruteForceServer.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    prS63BruteForceServer w;
    w.show();

    return a.exec();
}
