#include "TBlowfish.hpp"

#include <QString>

#include <memory>
#include <exception>

using namespace unitTest ;
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
 */
TBlowfish::TBlowfish(tdPtrBuf inPtrBuf)
{
    fPtrBuf = inPtrBuf ;
    fState = stLoad ;
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::setData Установка буфера с данными.
 * \param inPtrBuf  Указатель на массив данных которые нужно расшифровать и разархивировать
 */
void TBlowfish::setData (tdPtrBuf inPtrBuf)
{
    fPtrBuf.reset();
    fPtrBuf = inPtrBuf ;
    fState = stLoad ;
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::decryptPart    Расшифровка первых 8-ми байт массива.
 * \param inKey     Ключ для расшифровки
 * \return В случае получения сигнатуры zip файла, возвращает true
 */
bool TBlowfish::decryptPart (QString inKey)
{
    bool retVal {false} ;

    if (inKey.size() != 10) throw std::runtime_error("Ошибка тестового декодирования. Не правильный формат ключа!") ;
    if (fPtrBuf.use_count() == 0) throw std::runtime_error("Ошибка тестового декодирования. Нет данных!") ;
    switch (fState) {
      case stLoad :
      default :

      break ;



      case stPartSuccessful :
      case stFullSuccessful :
      case stUnzipSuccessful :
        throw std::runtime_error("Ошибка тестового дешифрирования. Данные уже расшифрованы!") ;
    }

    return retVal ;
}
//-----------------------------------------------------------------
/*!
 * \brief TBlowfish::decryptPart    Расшифровка первых 8-ми байт массива.
 * \param inPtrBuf  Указатель на массив данных которые нужно расшифровать
 * \param inKey     Ключ для расшифровки
 * \return          В случае получения сигнатуры zip файла, возвращает true
 */
bool TBlowfish::decryptPart (tdPtrBuf inPtrBuf, QString inKey)
{
    setData(inPtrBuf);
    return decryptPart (inKey) ;
}
//-----------------------------------------------------------------
bool TBlowfish::decryptFull (QString inKey)
{
    bool retVal {false} ;
    if (inKey.size() != 10) throw std::runtime_error("Ошибка полного дешифрированиея. Не правильный формат ключа!") ;

    if (fPtrBuf.use_count() == 0) throw std::runtime_error("Ошибка полного дешифрирования. Нет данных!") ;
    switch (fState) {
      case stLoad :
      case stPartSuccessful :

      break ;

      default:
        throw std::runtime_error("Ошибка полного дешифрирования. Нет данных!") ;
    }

    return retVal ;
}
//-----------------------------------------------------------------
bool TBlowfish::decryptFull (tdPtrBuf inPtrBuf)
{
    setData(inPtrBuf);
    return decryptFull () ;
}
//-----------------------------------------------------------------
bool TBlowfish::unzip (tdPtrBuf inPtrBuf)
{
    decryptFull (inPtrBuf);
}
//-----------------------------------------------------------------
bool TBlowfish::unzip ()
{
    switch (fState) {
      case stFullSuccessful:
      break ;

      default:
        throw std::runtime_error("Ошибка разархивации. Нет дешифрированных данных!") ;
    }

    if (fState != stFullSuccessful) throw std::runtime_error("Ошибка разархивации. Нет дешифрированных данных!") ;

}
//-----------------------------------------------------------------
void TBlowfish::writeFile (QString inFileName)
{
    if (fState != stUnzipSuccessful) throw std::runtime_error("Ошибка при записи файла " + inFileName.toStdString() + ". Нет раскодированных данных!") ;
}
//-----------------------------------------------------------------
