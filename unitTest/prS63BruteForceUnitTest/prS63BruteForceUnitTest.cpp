#include "prS63BruteForceUnitTest.hpp"
#include "ui_prS63BruteForceUnitTest.h"

prS63BruteForceUnitTest::prS63BruteForceUnitTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceUnitTest)
{
    ui->setupUi(this);
}

prS63BruteForceUnitTest::~prS63BruteForceUnitTest()
{
    delete ui;
}
