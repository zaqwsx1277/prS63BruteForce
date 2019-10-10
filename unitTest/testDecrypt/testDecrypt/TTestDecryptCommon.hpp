#ifndef TTESTDECRYPTCOMMON_H
#define TTESTDECRYPTCOMMON_H

#include <QtGlobal>

#include <memory>

namespace unitTest {

                /// Стрктура данных для вывода лога работе unit test TestDecrypt
    struct testDecryptLogData
    {
        QString fileName {""} ; /// Наименование обрабатываемого файла
        quint64 key {0} ;       /// Ключ для расшифровки
        quint64 inData {0} ;    /// Первые 8 байт из файла
        quint64 outData {0} ;   /// Расшифрованные первые 8 байт. Должны содержать сигнатуру zip-файла 0x04034B50
        bool result {false} ;   /// Результат расшифровки всего файла и получения S57
    };

    typedef std::shared_ptr <testDecryptLogData> tdPtrTestDecryptLogData ; /// typedef для указателя на testDecryptLogData
}

#endif // TTESTDECRYPTCOMMON_H
