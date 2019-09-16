#include "prS63BruteForceClient.hpp"
#include "ui_prS63BruteForceClient.h"

#include <array>
#include <memory>
#include <thread>

prS63BruteForceClient::prS63BruteForceClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceClient)
{


    ui->setupUi(this);

//    const unsigned int a = std::thread::hardware_concurrency();
    const int zzz = static_cast <const int> (std::thread::hardware_concurrency()) ;
    std::unique_ptr <std::array <QString, zzz>> xxx {nullptr} ;

}

prS63BruteForceClient::~prS63BruteForceClient()
{
    delete ui;
}
