#include "TException.hpp"

using namespace exception ;

//-------------------------------------------------------------------------------------
TExceptionCategory::TExceptionCategory(const char* inName, const std::string inMessage)
{
    fName = inName ;
    fMessage = inMessage ;
}
//-----------------------------------------------------
TExceptionCategory::TExceptionCategory(const TExceptionCategory& inOther)
{
    fName = inOther.fName ;
    fMessage = inOther.fMessage ;
}
//-----------------------------------------------------
const char* TExceptionCategory::name() const noexcept
{
    return fName ;
}
//-----------------------------------------------------
std::string TExceptionCategory::message(int) const
{
    return fMessage ;
}


//-----------------------------------------------------
TException::TException()
{

}
//-----------------------------------------------------
TException::TException(const std::string inTextError, const std::error_code& inCode)
{
    fCode = inCode ;
    fTextError = inTextError ;
}
//-----------------------------------------------------
const char* TException::what () const noexcept
{
    return fTextError.c_str() ;
}
//-----------------------------------------------------
const std::error_code& TException::code () const noexcept
{
    return fCode ;
}
//-----------------------------------------------------

