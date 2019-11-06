#ifndef TEXCEPTION_HPP
#define TEXCEPTION_HPP

#include <exception>
#include <system_error>

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
static const TException errConnectionSocket ("Ошибка инициализации сокета для работы с сервером!", {blowfushError + 1, blowfishCategory});

}
#endif // TEXCEPTION_HPP
