#include "TBlowfish.hpp"

#include <memory>
#include <exception>

#include <zlib.h>

using namespace blowfishLib ;

//------------------------------------------------------------------
/*!
 * \brief TBlowfish::TBlowfish  Конструктор класса
 */
TBlowfish::TBlowfish()
{
    fState = stUnknown ;
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::TBlowfish  Конструктор класса
 * \param inPtrBuf      Указатель на массив данных которые нужно расшифровать и разархивировать
 * \param inBufSize     Размер данного буфера
 */
TBlowfish::TBlowfish(tdPtrBuf inPtrBuf, quint32 inBufSize)
{
    setData(inPtrBuf, inBufSize);
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::clear  Очистка всех данных
 */
void TBlowfish::clear ()
{
    fPtrBuf.reset();
    fCipher.reset();
    fPtrBufUnZip.reset();
    fPtrBufDecrypt.reset();
    fState = stUnknown ;
    fBufSize = 0 ;
    fBufSizeUnzip = 0 ;
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::setData Установка буфера с данными.
 * \param inPtrBuf  Указатель на массив данных которые нужно расшифровать и разархивировать
 * \param inBufSize     Размер данного буфера
 */
void TBlowfish::setData (tdPtrBuf inPtrBuf, quint32 inBufSize)
{
    fPtrBuf.reset();
    fPtrBuf = inPtrBuf ;
    fBufSize = inBufSize ;
                                // Инициализируем буфер для раскодированных данных и класс для дешифровки
    fPtrBufDecrypt.reset( new Botan::uint8_t [inBufSize], [] (Botan::uint8_t* ptr) { delete [] ptr ; });
    if (!fCipher) fCipher = Botan::BlockCipher::create("Blowfish") ;
    fState = stLoad ;
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::decryptPart    Расшифровка первых 8-ми байт массива.
 * \param inKey                     Ключ для расшифровки
 * \return                          В случае получения сигнатуры zip файла, возвращает true
 */
bool TBlowfish::decryptPart (QString inKey)
{
    bool retVal {false} ;

    if (inKey.remove(" ").size() != 10)
        throw blowfishExeption::errTestDecryptFormatKey ;
    if (fPtrBuf.use_count() == 0) throw blowfishExeption::errTestDecryptNoData ;
    switch (fState) {
      case stLoad : {            // дешифрируем первые 8 байт
        std::vector<uint8_t> key = Botan::hex_decode(inKey.toStdString()) ;
        fCipher -> set_key (key) ;
        fCipher -> decrypt_n (fPtrBuf.get(), fPtrBufDecrypt.get(), 1) ;
        if (checkDecrypt ()) {
            fState = stPartSuccessful ;
            retVal = true ;
        }
          else fState = stUnsuccessful ;
      }
      break ;

      default :
        throw blowfishExeption::errTestDecryptUnknowState  ;
      break ;

      case stUnsuccessful :
      case stPartSuccessful :
      case stFullSuccessful :
      case stUnzipSuccessful :
        throw blowfishExeption::errTestDecryptAlreadyDecrypt ;
      break ;
    }

    return retVal ;
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::decryptFull    Полная расшифровка буфера
 * \param inKey                     Ключ для расшифровки
 * \return                          В случае получения сигнатуры zip файла, возвращает true
 *
 * Проверка декодирования выполняется только по первым 4 байтам на соответствие сигнатуре zip файла.
 * Для полной проверки правильности дешифрации нужно выполнить разархивацию файла.
 */
bool TBlowfish::decryptFull (QString inKey)
{
    bool retVal {false} ;
    if (inKey.remove(" ").size() != 10) throw blowfishExeption::errFullDecryptFormatKey  ;

    if (fPtrBuf.use_count() == 0) throw blowfishExeption::errFullDecryptNoData  ;
    switch (fState) {
      case stLoad :
      case stPartSuccessful : {
        auto blokSize = fCipher -> block_size() ;       // Размер блока. Для blowfish размер блока 8 байт
        for (size_t i = 0; i <  (fBufSize) / blokSize; i++)
            fCipher -> decrypt(fPtrBuf.get() + (i * blokSize), fPtrBufDecrypt.get() + (i * blokSize)) ;
        if (checkDecrypt ()) {
            fState = stFullSuccessful ;
            retVal = true ;
        }
          else fState = stUnsuccessful ;
      }
      break ;

      default:
        throw blowfishExeption::errFullDecryptNoData ;
    }

    return retVal ;
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::unzip  Разархивация декодированного буфера
 * \return                  Вслучаем успешной разархивации возвращается true
 *
 * Для разврхивации используется zlib.
 * В дальнейшем, если возможно, то нужно переделать на использование Botan::Zlib_Decompression
 */
bool TBlowfish::unzip ()
{
    bool retVal {false} ;
    switch (fState) {
      case stFullSuccessful: {
        zipLocalFileHeader *localFileHeader = reinterpret_cast <zipLocalFileHeader *> (fPtrBufDecrypt.get()) ;

        if (localFileHeader -> signature == zipHeaderSignature) {
            quint64 inLength = localFileHeader -> compressedSize ;
            fBufSizeUnzip = localFileHeader -> uncompressedSize ;
            Bytef *ptrInBuf = reinterpret_cast <Bytef*> (localFileHeader) ;
            ptrInBuf = ptrInBuf + sizeof (zipLocalFileHeader) + localFileHeader -> filenameLength + localFileHeader -> extraFieldLength ;
            fPtrBufUnZip.reset(new std::uint8_t [localFileHeader -> uncompressedSize]);

            z_stream ZipStream = {} ;
            if (inflateInit2(&ZipStream,-MAX_WBITS) == Z_OK) {
                ZipStream.next_in  = ptrInBuf ;
                ZipStream.avail_in = static_cast<uInt> (inLength) ;
                ZipStream.next_out  = reinterpret_cast <Bytef*> (fPtrBufUnZip.get()) ;
                ZipStream.avail_out = static_cast<uInt> (fBufSizeUnzip) ;

                int err = 0;                                // Выполняем разархивацию
                err = inflate(&ZipStream,Z_SYNC_FLUSH);
                if ((err == Z_OK) || (err == Z_STREAM_END)) {
                    retVal = true ;                 // Разархивация выполнена успешно
                    fState = stUnzipSuccessful ;
                }
            }
        }
      }
      break ;

      default:
        throw blowfishExeption::errUnzipNoData ;
    }

    return retVal ;
}
//-----------------------------------------------------------------
void TBlowfish::writeFile (QString inFileName)
{
    if (fState != stUnzipSuccessful) throw blowfishExeption::errWriteFileNoData  ;
    Botan::DataSink_Stream writeStream (inFileName.toStdString(), true) ;
    writeStream.write(fPtrBufUnZip.get(), fBufSizeUnzip);
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::checkDecrypt   Проверка сигнатуры zip-файл 0x04034B50 в первых 4х байтах
 * \return                          Если сигнатура
 */
bool TBlowfish::checkDecrypt ()
{
    bool retVal {false} ;

    switch (fState) {
      case stLoad :
      case stPartSuccessful :    // Проверка выполняется только если выполнялось дешифрирование
      case stFullSuccessful :
        if (fPtrBufDecrypt [0] == 0x50 && fPtrBufDecrypt [1] == 0x4B && fPtrBufDecrypt [2] == 3 && fPtrBufDecrypt [3] == 4) retVal = true ;
      break ;

      default :
        throw blowfishExeption::errCheckZip ;
      break ;
    }

    return retVal ;
}
//-----------------------------------------------------------------
/*!
 * \brief getDecryptBuf Возвращает дешифрованный буфер. Размер буфера равен исходному.
 * \return              Указатель на буфер с преобразованными данными
 */
tdPtrBuf TBlowfish::getDecryptBuf ()
{
    return fPtrBufDecrypt ;
}
//-----------------------------------------------------------------
