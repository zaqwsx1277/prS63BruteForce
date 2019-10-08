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
    enum state {stUnknown, stLoad, stPartSuccessful, stFullSuccessful, stUnzipSuccessful} ; // Состояния декодирования. Нужны для подбора ключей.

    state fState {stUnknown} ;      // Состояние по подбору пароля
    tdPtrBuf fPtrBuf {nullptr} ;    // Указатель на буфер с обрабатываемыми данными
    tdPtrBuf fPtrBufDecrypt {nullptr} ; // Указатель на буфер с дешифрированными данными
    qint32 fBufSize {0} ;           // Размер буферf с обрабатываемыми данными. Нужен для формирования буфера для дешифрирования
public:
    TBlowfish(tdPtrBuf, quint32);   // Конструктор инициализируемый буфером с данными
    TBlowfish();

    void clear () ;                 // Очистка всех данных

    void setData (tdPtrBuf, quint32) ; // Загрузка данных которые нужно дешифрировать
    bool decryptPart (QString) ;    // Дешифровка первых восьми байт
    bool decryptFull (QString) ;    // Полная дешифровка данных
    bool unzip () ;                 // Выполнение разархивации
    void writeFile (QString) ;      // Запись полностью декодированного файла
    tdPtrBuf getDecryptBuf () ;     // Возвращает дешифрованный буфер. Размер буфера равен исходному.
};

}
#endif // TBLOWFISH_H
