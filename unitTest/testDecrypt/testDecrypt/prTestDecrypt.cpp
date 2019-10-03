#include "prTestDecrypt.hpp"
#include "ui_prTestDecrypt.h"

#include <QFileDialog>
#include <QFileInfo>

#include <botan/data_snk.h>
#include <botan/hex.h>
#include <botan/blowfish.h>
#include <botan/data_src.h>

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
    connect(ui -> spLogView -> model(), &QAbstractTableModel::rowsInserted, ui -> spLogView, &QTableView::scrollToBottom) ;    // Устанавливаем текущей последнюю строку
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
        ui -> spPathTo ->setText(pathS57) ;
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
    logData -> key = (ui -> spKey ->text().remove(" ")).toULongLong(nullptr, 16) ;
    size_t fileLength = fileInfo.size() ;
    std::shared_ptr <Botan::uint8_t []> readBuf (new Botan::uint8_t [fileLength]) ;
    std::shared_ptr <Botan::uint8_t []> decryptBuf (new Botan::uint8_t [fileLength]) ;
    Botan::DataSource_Stream in (ui -> spPathFrom -> text().toStdString(), true) ;
    size_t fileRead = in.read(readBuf.get(), fileLength) ;
    std::string xx = Botan::hex_encode(readBuf.get(), 8, true) ;
    logData -> inData = (QString::fromStdString(xx)).toULongLong(nullptr, 16) ;

    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("Blowfish")) ;
    std::vector<uint8_t> key = Botan::hex_decode(ui -> spKey ->text().toStdString()) ;
    cipher -> set_key (key) ;
    cipher -> decrypt_n (readBuf.get(), decryptBuf.get(), 1) ;

    std::string zz = Botan::hex_encode(decryptBuf.get(), 8, true) ;
    logData -> outData = (QString::fromStdString(zz)).toULongLong(nullptr, 16) ;
    if (decryptBuf [0] == 0x50 && decryptBuf [1] == 0x4B && decryptBuf [2] == 3 && decryptBuf [3] == 4) {
        auto blokSize = cipher -> block_size() ;
        for (size_t i = 0; i <  (fileLength) / blokSize; i++)
            cipher -> decrypt(readBuf.get() + (i * blokSize), decryptBuf.get() + (i * blokSize)) ;
        zipLocalFileHeader *ptrZipHeader = reinterpret_cast <zipLocalFileHeader *> (decryptBuf.get()) ;
        auto offset = sizeof (zipLocalFileHeader) + ptrZipHeader -> filenameLength + ptrZipHeader -> extraFieldLength ;
        Botan::secure_vector <uint8_t> unzipBuf ;
        for (size_t i = offset; i < fileLength; i++) unzipBuf.push_back(decryptBuf [i]);
        std::unique_ptr<Botan::Zlib_Decompression> unzip (new Botan::Zlib_Decompression ()) ;
//        unzip -> finish (unzipBuf, 0) ;


        logData -> result = true ;
    }


    fPrtLogModel -> push_back(logData) ;
}
//---------------------------------------------------------------------------------------------
