#ifndef PRTESTDECRYPT_HPP
#define PRTESTDECRYPT_HPP

#include <QMainWindow>

#include "TTestDecryptLogModel.hpp"


namespace Ui {
class prTestDecrypt;
}

namespace unitTest {

#ifdef Q_OS_WIN
    #pragma pack(push, 1)
#endif
    typedef struct LocalFileHeader                          // typedef Описание метаданных работы с ZIP
        {
            uint32_t signature;             // Обязательная сигнатура, равна 0x04034b50
            uint16_t versionToExtract;      // Минимальная версия для распаковки
            uint16_t generalPurposeBitFlag; // Битовый флаг
            uint16_t compressionMethod;     // Метод сжатия (0 - без сжатия, 8 - deflate)
            uint16_t modificationTime;      // Время модификации файла
            uint16_t modificationDate;      // Дата модификации файла
            uint32_t crc32;                 // Контрольная сумма
            uint32_t compressedSize;        // Сжатый размер
            uint32_t uncompressedSize;      // Несжатый размер
            uint16_t filenameLength;        // Длина название файла
            uint16_t extraFieldLength;      // Длина поля с дополнительными данными
        }
#ifdef Q_OS_UNIX
    __attribute__((packed))
#endif
          zipLocalFileHeader ;

#ifdef Q_OS_WIN
    #pragma pack(pop)
#endif

//---------------------------------------------------------------------------
/*!
 * \brief Unit Test для отработки библиотечных функций декодирования и разархивации файла S63 в S57
 */
class prTestDecrypt : public QMainWindow
{
    Q_OBJECT

public:
    explicit prTestDecrypt(QWidget *parent = 0);
    ~prTestDecrypt();

private slots:
    void on_btnPathFrom_clicked();
    void on_btnPathTo_clicked();

    void on_btnConvert_clicked();

private:
    Ui::prTestDecrypt *ui;

    std::unique_ptr <TTestDecryptLogModel> fPrtLogModel {nullptr} ; // Указатель на модель для отображения лога работы юнит теста
};

}

#endif // PRTESTDECRYPT_HPP
