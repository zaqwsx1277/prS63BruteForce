#ifndef TBLOWFISH_H
#define TBLOWFISH_H

#include <QtGlobal>

#include <botan/data_snk.h>
#include <botan/hex.h>
#include <botan/blowfish.h>
#include <botan/data_src.h>

namespace unitTest {


    typedef std::shared_ptr <Botan::uint8_t []> tdPtrBuf ; //(new Botan::uint8_t [] (Botan::uint8_t *) {delete p}> tdPtrBuf ;  // Указатель на буфер с обрабатываемыми данными.

/*!
 * \brief Класс выполняющий декодирование S63 и запись файла S57
 */
class TBlowfish
{
private:
    enum state {stUnknown, stLoad, stPartSuccessful, stFullSuccessful, stUnSuccessful} ; // Состояния декодирования. Нужны для подбора ключей.

    state fState {stUnknown} ;      // Состояние по подбору пароля
    tdPtrBuf fPtrBuf {nullptr} ;    // Указатель на буфер с обрабатываемыми данными
public:
    TBlowfish(tdPtrBuf);            // Конструктор инициализируемый буфером с данными
    TBlowfish();

    void setData (tdPtrBuf) ;       // Загрузка данных которые нужно дешифрировать
    bool decryptPart () ;           // Дешифровка первых восьми байт
    bool decryptPart (tdPtrBuf) ;   // Дешифровка первых восьми байт
    bool decryptFull () ;           // Полная дешифровка данных
    bool unzip (tdPtrBuf) ;         // Выполнение разархивации
    bool unzip () ;                 // Выполнение разархивации
    void write (QString) ;          // Запись полностью декодированного файла
};

}
#endif // TBLOWFISH_H
