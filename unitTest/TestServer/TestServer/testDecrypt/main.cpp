#include "testDecryptMainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testDecryptMainWindow w;
    w.show();

    return a.exec();
}
