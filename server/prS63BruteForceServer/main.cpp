#include "prS63BruteForceServer.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server::prS63BruteForceServer w;
    w.show();

    return a.exec();
}
