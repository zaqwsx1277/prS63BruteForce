#ifndef TTESTDECRYPTCOMMON_H
#define TTESTDECRYPTCOMMON_H

#include <QString>

namespace unitTest {

/// Стрктура данных для вывода лога работе unit test TestDecrypt
struct testDecryptLogData
{
    QString fileName {""} ; /// Наименование обрабатываемого файла
};
}

#endif // TTESTDECRYPTCOMMON_H
