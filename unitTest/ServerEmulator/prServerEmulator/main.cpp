#include "prServerEmulator.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    prServerEmulator w;
    w.show();

    return a.exec();
}
