#ifndef TBLOWFISH_H
#define TBLOWFISH_H

#include <QtGlobal>
#include <QString>

#include <botan/data_snk.h>
#include <botan/hex.h>
#include <botan/blowfish.h>
#include <botan/data_src.h>

#include <memory>
#include <exception>
#include <system_error>

namespace unitTest {

#ifdef Q_OS_WIN
    #pragma pack(push, 1)
#endif
                        ///  Описание метаданных работы с ZIP
    typedef struct LocalFileHeader
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

    const uint32_t zipHeaderSignature { 0x04034B50 } ;  // Сигнатура начала LocalFileHeader (обычно с него начинается zip-файл)
//--------------------------------------------------------------------------
        /// Описание различных typedef

    typedef std::shared_ptr <Botan::uint8_t []> tdPtrBuf ;   // Указатель на буфер с обрабатываемыми данными.
//--------------------------------------------------------------------------
namespace blowfishExeption {

/*!
 * \brief Структура для формирования std::error_code для класса декодирования
 *
 */
class TBlowfishExeptionCategory : public std::error_category
{
public:
    TBlowfishExeptionCategory () : std::error_category () { ; }
    const char* name () const noexcept { return "Blowfish error" ; }
    std::string message(int inEx = 0) const {  return "Blowfish error" ; }
} ;

const TBlowfishExeptionCategory blowfishExeptionCategory {} ;

/*!
 * \brief Класс обработки ошибок при декодировании
 */
class TBlowfishExeption : public std::exception {

    std::string fTextError {"Blowfish error."} ;
    std::error_code fErrorCode {0, TBlowfishExeptionCategory() } ;
public:
    TBlowfishExeption () = default ;
    TBlowfishExeption (std::error_code inErrorCode, std::string inTextError) { fErrorCode = inErrorCode; fTextError = inTextError ; }
    const char* what () const throw () { return fTextError.c_str() ; }
    const std::error_code& code () const noexcept {return fErrorCode ; }
} ;

static const std::uint32_t blowfushError {1000} ;
static const TBlowfishExeption errTestDecryptFormatKey ({blowfushError + 1, blowfishExeptionCategory}, "Ошибка тестового декодирования. Неправильный формат ключа!");
static const TBlowfishExeption errTestDecryptNoData ({blowfushError + 2, blowfishExeptionCategory}, "Ошибка тестового декодирования. Нет данных!");
static const TBlowfishExeption errTestDecryptUnknowState ({blowfushError + 3, blowfishExeptionCategory}, "Ошибка тестового дешифрирования. Непонятное состояние!");
static const TBlowfishExeption errTestDecryptAlreadyDecrypt ({blowfushError + 4, blowfishExeptionCategory}, "Ошибка тестового дешифрирования. Данные уже расшифрованы!");
static const TBlowfishExeption errFullDecryptFormatKey ({blowfushError + 5, blowfishExeptionCategory}, "Ошибка полного дешифрированиея. Не правильный формат ключа!");
static const TBlowfishExeption errFullDecryptNoData ({blowfushError + 6, blowfishExeptionCategory}, "Ошибка полного дешифрирования. Нет данных!");
static const TBlowfishExeption errUnzipNoData ({blowfushError + 7, blowfishExeptionCategory}, "Ошибка разархивации. Нет дешифрированных данных!");
static const TBlowfishExeption errWriteFileNoData ({blowfushError + 8, blowfishExeptionCategory}, "Ошибка при записи файла. Нет раскодированных данных!");
static const TBlowfishExeption errCheckZip ({blowfushError + 9, blowfishExeptionCategory}, "Ошибка статуса при проверке сигнатуры zip-файла");
}
//--------------------------------------------------------------------------
/*!
 * \brief Класс выполняющий декодирование S63 и запись файла S57
 */
class TBlowfish
{
private:
    enum state {stUnknown, stLoad, stPartSuccessful, stFullSuccessful, stUnzipSuccessful, stUnsuccessful} ; // Состояния декодирования. Нужны для подбора ключей.

    state fState {stUnknown} ;      // Состояние по подбору пароля
    tdPtrBuf fPtrBuf {nullptr} ;    // Указатель на буфер с обрабатываемыми данными
    tdPtrBuf fPtrBufDecrypt {nullptr} ; // Указатель на буфер с дешифрированными данным
    std::unique_ptr <Botan::uint8_t []> fPtrBufUnZip {nullptr} ; // Указатель на буфер с дешифрированными данным
    std::unique_ptr <Botan::BlockCipher> fCipher {nullptr} ; // Указатель на класс дешифрации blowfish

    qint32 fBufSize {0} ;           // Размер буфера с обрабатываемыми данными. Нужен для формирования буфера для дешифрирования
    qint32 fBufSizeUnzip {0} ;      // Размер буфера с разархивированными данными
public:
    TBlowfish(tdPtrBuf, quint32);   // Конструктор инициализируемый буфером с данными
    TBlowfish();

    void clear () ;                 // Очистка всех данных

    void setData (tdPtrBuf, quint32) ;  // Загрузка данных которые нужно дешифрировать
    bool decryptPart (QString) ;        // Дешифровка первых восьми байт
    bool decryptFull (QString) ;        // Полная дешифровка данных
    bool unzip () ;                     // Выполнение разархивации
    void writeFile (QString) ;          // Запись полностью декодированного файла
    tdPtrBuf getDecryptBuf () ;         // Возвращает дешифрованный буфер. Размер буфера равен исходному.
    bool checkDecrypt () ;              // Проверка сигнатуры zip-файла
};

}
#endif // TBLOWFISH_H
