#include "prS63BruteForceServer.hpp"
#include <QApplication>

#include "TDataModule.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TDataModule& fCommonData = TDataModule::instance(); // Инициализация общих данных для проекта

    server::prS63BruteForceServer w;
    w.show();

    return a.exec();
}
