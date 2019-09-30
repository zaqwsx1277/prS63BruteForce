#include "prTestDecrypt.hpp"
#include "ui_prTestDecrypt.h"

#include <QFileDialog>

using namespace unitTest ;
//--------------------------------------------------------------------------------------------
prTestDecrypt::prTestDecrypt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prTestDecrypt)
{
    ui->setupUi(this);

    ui -> spPathFrom -> clear();
    ui -> spPathTo -> clear();
    ui -> spKey -> clear () ;
}
//--------------------------------------------------------------------------------------------
prTestDecrypt::~prTestDecrypt()
{
    delete ui;
}
//---------------------------------------------------------------------------------------------
/*!
 * \brief prTestDecrypt::on_btnPathFrom_clicked Слот обрабатывающий выбор исходного файла S63
 */
void prTestDecrypt::on_btnPathFrom_clicked()
{
    QString pathS63 = QFileDialog::getOpenFileName (this, "Открыть папку с исходным файлом S63", ui -> spPathFrom -> text());
    if (!pathS63.isEmpty()) {
        ui -> spPathFrom ->setText(pathS63) ;
    }
}
//---------------------------------------------------------------------------------------------
/*!
 * \brief prTestDecrypt::on_btnPathTo_clicked   Слот обрабатывающий выбор результурующего файла S57
 */
void prTestDecrypt::on_btnPathTo_clicked()
{
    QString pathS57 = QFileDialog::getExistingDirectory(this, tr("Открыть папку для результурующего файла S57"), ui -> spPathFrom -> text(), QFileDialog::ShowDirsOnly);
    if (!pathS57.isEmpty()) {
        ui -> spPathFrom ->setText(pathS57) ;
    }
}
//---------------------------------------------------------------------------------------------
void unitTest::prTestDecrypt::on_btnConvert_clicked()
{

}
//---------------------------------------------------------------------------------------------
