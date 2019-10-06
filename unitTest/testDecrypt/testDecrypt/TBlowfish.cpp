#include "TBlowfish.hpp"

#include <memory>

using namespace unitTest ;
//------------------------------------------------------------------
TBlowfish::TBlowfish()
{
    fState = stUnknown ;
}
//-----------------------------------------------------------------
TBlowfish::TBlowfish(tdPtrBuf inPtrBuf)
{
    fPtrBuf = inPtrBuf ;
    fState = stLoad ;
}
//-----------------------------------------------------------------
void TBlowfish::setData (tdPtrBuf inPtrBuf)
{
    fPtrBuf = inPtrBuf ;
    fState = stLoad ;
}
//-----------------------------------------------------------------
bool decryptPart ()
{

}
//-----------------------------------------------------------------
bool decryptPart (tdPtrBuf)
{

}
//-----------------------------------------------------------------
bool decryptFull ()
{

}
//-----------------------------------------------------------------
bool unzip (tdPtrBuf)
{

}
//-----------------------------------------------------------------
bool unzip ()
{

}
//-----------------------------------------------------------------
void write (QString inFileName)
{

}
//-----------------------------------------------------------------
