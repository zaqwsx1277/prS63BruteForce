#include "prS63BruteForceClient.hpp"
#include "ui_prS63BruteForceClient.h"
#include "TCommonDefine.hpp"

#include <thread>


//---------------------------------------------------------------------
prS63BruteForceClient::prS63BruteForceClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prS63BruteForceClient)
{
    ui->setupUi(this);

    initForm () ;
    clearForm () ;
}
//----------------------------------------------------------------------
prS63BruteForceClient::~prS63BruteForceClient()
{
    delete ui;
}
//----------------------------------------------------------------------
/*!
 * \brief prS63BruteForceClient::initForm   инициализирую все элементы формы
 */
void prS63BruteForceClient::initForm ()
{
                                    // задаём все необходимые регулярные выражения

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    ui -> spServerAddress -> setValidator( new QRegExpValidator( QRegExp( "^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$")));

}

/*!
 * \brief prS63BruteForceClient::clearForm  Очищаем и устанавливаем начальные значения всех элементов формы
 */
void prS63BruteForceClient::clearForm ()
{
    ui -> spServerAddress -> clear() ;
    ui -> spServerPort -> setText (QString::number(commonDefine::portNumber)) ;
    ui -> spBlockSize -> clear() ;
}
//----------------------------------------------------------------------
