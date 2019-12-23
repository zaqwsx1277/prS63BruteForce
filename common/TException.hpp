#ifndef TEXCEPTION_HPP
#define TEXCEPTION_HPP

#include <exception>
#include <system_error>

#include <string>

namespace exception {
//-----------------------------------------------------------------------------
/*!
 * \brief Класс описывающий категорию ошибок для проекта
 */
class TExceptionCategory : public std::error_category
{
public:
    TExceptionCategory() { ; }
    TExceptionCategory(const char*, const std::string);
    TExceptionCategory(const TExceptionCategory&);

    virtual const char* name() const noexcept override;
    std::string message(int) const override;

protected:
    const char* fName {"Blowfish"} ;
    std::string fMessage {"Blowfish"};
} ;
static const TExceptionCategory blowfishCategory ("Blowfish", "Blowfish");
//----------------------------------------------------
/*!
 * \brief Класс обработки ошибок
 */
class TException : public std::exception
{
public:
    TException();
    TException(const std::string, const std::error_code &inCode = {0, blowfishCategory});

    const char* what () const noexcept;
    const std::error_code& code () const noexcept;

private:
    std::string fTextError {"No error"};
    std::error_code fCode {0, blowfishCategory};
};

static const std::uint32_t blowfushError {1000} ;
static const TException noError ("Ошибки отсутствуют!");

static const std::string warning {"Предупреждение"} ;   // Типв сообщений об шибках
static const std::string criticalError {"Критическая ошибка"} ;

static const TException errConnectionSocket ("Ошибка инициализации сокета для работы с сервером!", {blowfushError + 1, blowfishCategory});
                // Прерывания генерируемые при передаче данных
static const TException errTransferLost ("Потеря полученных данных!", {blowfushError + 2, blowfishCategory});
static const TException errTransferNoTitle ("Ошибка заголовка кадра!", {blowfushError + 3, blowfishCategory});
static const TException errTransferNoCommand ("Ошибка в формате коменды!", {blowfushError + 4, blowfishCategory});
static const TException errTransferLostSequence ("Потеряна последовательность передачи!", {blowfushError + 5, blowfishCategory});
                // Прерывания генерируемые сервером
static const TException errServerSecondInstance ("Повторный запуск подбора!", {blowfushError + 6, blowfishCategory});
static const TException errServerUnknownState ("Неизвестное состояние!", {blowfushError + 7, blowfishCategory});
}
#endif // TEXCEPTION_HPP
