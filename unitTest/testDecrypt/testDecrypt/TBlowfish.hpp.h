#ifndef TBLOWFISH_H
#define TBLOWFISH_H


#include <botan/data_snk.h>
#include <botan/hex.h>
#include <botan/blowfish.h>
#include <botan/data_src.h>

namespace unitTest {

/*!
 * \brief Класс выполняющий декодирование S63 и запись файла S57
 */
class TBlowfish
{
private:
    enum state {stUnknown, stLoad, stPartSuccessful, stFullSuccessful, stUnSuccessful} ; // Состояния декодирования. Нужны для подбора ключей.

    state fState {stUnknown} ;  // Состояние по подбору пароля
public:
    TBlowfish();

    void setData () ;       // Загрузка данных которые нужно дешифрировать
    bool decryptPart () ;   // Дешифровка первых восьми байт
    bool decryptFull () ;   // Полная дешифровка данных
    bool unzip () ;         // Выполнение разархивации
    void write () ;         // Запись полностью декодированного файла
};

}
#endif // TBLOWFISH_H
