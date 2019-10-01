#include "prTestDecrypt.hpp"
#include "ui_prTestDecrypt.h"

#include <QFileDialog>
#include <QFileInfo>

//#include <botan/asn1_time.h>
//#include <botan/pk_keys.h>
#include <botan/data_snk.h>
//#include <botan/hex.h>
#include <botan/blowfish.h>
#include <botan/data_src.h>
//#include <botan/pk_ops.h>
//#include <botan/hash.h>

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

    fPrtLogModel.reset( new TTestDecryptLogModel ());
    ui -> spLogView -> setModel(fPrtLogModel.get()) ;                             // Инициализируем таблицу для ведения лога
    for (int i = 0; i < fPrtLogModel -> columnCount(); i++) {
      ui-> spLogView -> horizontalHeader() -> setSectionResizeMode(i, QHeaderView::Stretch) ;
    }
//    connect(ui -> spLogView -> model(), &QAbstractTableModel::rowsInserted, ui -> spLogView, &QTableView::scrollToBottom) ;    // Устанавливаем текущей последнюю строку
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
/*!
 * \brief unitTest::prTestDecrypt::on_btnConvert_clicked    Слот обрабатывающий нажатие на кнопку выполнения преобразования
 */
void unitTest::prTestDecrypt::on_btnConvert_clicked()
{
    tdPtrTestDecryptLogData logData (new testDecryptLogData) ;
    QFileInfo fileInfo = QFileInfo (ui -> spPathFrom -> text()) ;

    logData -> fileName = fileInfo.fileName() ;
    size_t fileLength = fileInfo.size() ;
    std::shared_ptr <Botan::uint8_t []> readBuf (new Botan::uint8_t [fileLength]) ;
    Botan::DataSource_Stream in (ui -> spPathFrom -> text().toStdString(), true) ;
    size_t fileRead = in.read(readBuf.get(), fileLength) ;


    fPrtLogModel -> push_back(logData) ;
}
//---------------------------------------------------------------------------------------------
