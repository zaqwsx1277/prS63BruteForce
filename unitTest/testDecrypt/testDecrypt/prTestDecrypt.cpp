#include "prTestDecrypt.hpp"
#include "ui_prTestDecrypt.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include <botan/data_snk.h>
#include <botan/hex.h>
#include <botan/blowfish.h>
#include <botan/data_src.h>

#include <system_error>

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
    tdPtrTestDecryptLogData logData (new testDecryptLogData) ;  // формируем структуру для записи лога
    try {
        QFileInfo fileInfo = QFileInfo (ui -> spPathFrom -> text()) ;

        logData -> fileName = fileInfo.fileName() ;                 // Читаем файл к которому нужно подобрать ключ
        logData -> key = (ui -> spKey ->text().remove(" ")).toULongLong(nullptr, 16) ;
        size_t fileLength = fileInfo.size() ;
                                                                    // Буфер в который читается файл
        std::shared_ptr <Botan::uint8_t []> readBuf (new Botan::uint8_t [fileLength], [] (Botan::uint8_t* ptr) { delete [] ptr ; }) ;
                                                                    // Чтение файла
        Botan::DataSource_Stream inBuf (ui -> spPathFrom -> text().toStdString(), true) ;
        size_t fileRead = inBuf.read(readBuf.get(), fileLength) ;
        if (fileRead != fileLength) throw std::runtime_error("Ошибка при чтении файла!") ;
                                                                    // Запись в лог первых 8ми байт
        std::string inBufFirst8 = Botan::hex_encode(readBuf.get(), 8, true) ;
        logData -> inData = (QString::fromStdString(inBufFirst8)).toULongLong(nullptr, 16) ;

        std::unique_ptr <TBlowfish> blowfish {new TBlowfish (readBuf, fileRead)} ;
                                                                    // Раскодировка и в случае успеха запись файла
        if (!blowfish -> decryptPart(ui -> spKey ->text())) throw std::runtime_error("Ошибка декодирования первых 8-ми байт!") ;
        if (!blowfish -> decryptFull(ui -> spKey ->text())) throw std::runtime_error("Ошибка декодирования файла!") ;
                                                                    // Запись в лог первых расшифрованных 8ми байт
        std::string outBufFirst8 = Botan::hex_encode(blowfish -> getDecryptBuf().get(), 8, true) ;
        logData -> outData = (QString::fromStdString(outBufFirst8)).toULongLong(nullptr, 16) ;

        if (!blowfish -> unzip()) throw std::runtime_error("Ошибка разархивации файла!") ;
          else logData -> result = true ;
        QString unzipFileName = ui -> spPathTo -> text() + "/" + fileInfo.fileName() ;
        blowfish -> writeFile (unzipFileName);

        fPrtLogModel -> push_back(logData) ;
    }
      catch (blowfishExeption::TBlowfishExeption& ex) {
        fPrtLogModel -> push_back(logData) ;
        QMessageBox::critical(this, "Ошибка приложения", QString::fromStdString(ex.what()), QMessageBox::Ok) ;
      }
//      catch (std::exception &ex) {
//        fPrtLogModel -> push_back(logData) ;
//        QMessageBox::critical(this, "Ошибка приложения", QString::fromStdString(ex.what()), QMessageBox::Ok) ;
//      }

      catch (...) {
        fPrtLogModel -> push_back(logData) ;
        QMessageBox::critical(this, "Ошибка приложения", "Общая ошибка приложения!", QMessageBox::Ok) ;
      }
}
//---------------------------------------------------------------------------------------------

void unitTest::prTestDecrypt::on_toolButton_clicked()
{
    try {
        TBlowfish *xxx = new (TBlowfish) ;
        xxx ->writeFile("vvvvv");
    }
      catch (std::exception &ex) {
        QMessageBox::critical(this, "Ошибка приложения", QString::fromStdString(ex.what()), QMessageBox::Ok) ;
      }

      catch (...) {
        QMessageBox::critical(this, "Ошибка приложения", "Общая ошибка приложения!", QMessageBox::Ok) ;
      }


}
