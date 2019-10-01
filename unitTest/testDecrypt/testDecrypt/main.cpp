#include "prTestDecrypt.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    unitTest::prTestDecrypt w;
    w.show();

    return a.exec();
}
