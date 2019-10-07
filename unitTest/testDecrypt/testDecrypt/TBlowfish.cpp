#include "TBlowfish.hpp"

#include <QString>

#include <memory>

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
/
void TBlowfish::setData (tdPtrBuf inPtrBuf)
{
    fPtrBuf.reset();
    fPtrBuf = inPtrBuf ;
    fState = stLoad ;
}
//-----------------------------------------------------------------
bool TBlowfish::decryptPart ()
{
    bool retVal {false} ;

    if (fPtrBuf.use_count() == 0) throw std::runtime_error("Ошибка тестового декодирования. Нет данных!") ;
    switch (fState) {
      case stLoad :
      default :

      break ;

      case stPartSuccessful :
      case stFullSuccessful :
      case stUnzipSuccessful :
        throw std::runtime_error("Ошибка тестового декодирования. Данные уже декодированны!") ;
    }

    return retVal ;
}
//-----------------------------------------------------------------
bool TBlowfish::decryptPart (tdPtrBuf inPtrBuf)
{
    setData(inPtrBuf);
}
//-----------------------------------------------------------------
bool TBlowfish::decryptFull ()
{
    if (fPtrBuf.use_count() == 0) throw std::runtime_error("Ошибка полного декодирования. Нет данных!") ;
    switch (fState) {
      case stLoad :
      case stPartSuccessful :

      break ;

      default:
        throw std::runtime_error("Ошибка полного декодирования. Нет данных!") ;
    }
}
//-----------------------------------------------------------------
bool TBlowfish::decryptFull (tdPtrBuf inPtrBuf)
{
    setData(inPtrBuf);
    decryptFull () ;
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
