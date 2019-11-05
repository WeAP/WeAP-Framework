
#include "Exception.h"



namespace WeAP{ namespace System {



Exception::Exception(int errorCode, 
                   const string& errorMessage) throw()
{
    this->Init(errorCode, 
               errorMessage);
}


Exception::Exception(int errorCode, 
                   const string& errorMessage, 
                   int innerErrorCode,
                   const string& innerErrorMessage) throw()
{
    this->Init(errorCode, 
               errorMessage, 
               innerErrorCode,
               innerErrorMessage);
}

Exception::Exception(int errorCode, 
                   const string& errorMessage, 
                   const string& fileName, 
                   int lineNo) throw()
{
    this->Init(errorCode, 
               errorMessage, 
               Exception::InvalidErrorCode,
               "",
               fileName,
               lineNo);
}

Exception::Exception(int errorCode, 
                   const string& errorMessage, 
                   int innerErrorCode,
                   const string& innerErrorMessage, 
                   const string& fileName, 
                   int lineNo) throw()
{
    this->Init(errorCode, 
               errorMessage, 
               innerErrorCode,
               innerErrorMessage,
               fileName,
               lineNo);
}

Exception::Exception(const Exception& other)  throw()
{
    this->Init(other);
}

Exception::~Exception()  throw()
{

}

Exception& Exception::operator=(const Exception& other)  throw()
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Exception::Init(const Exception& other)  throw()
{
    this->Init(other.errorCode,
               other.errorMessage,
               other.innerErrorCode,
               other.innerErrorMessage,
               other.fileName,
               other.lineNo);
    
}


void Exception::Init(int errorCode, 
                       const string& errorMessage, 
                       int innerErrorCode,
                       const string& innerErrorMessage, 
                       const string& fileName,
                       int lineNo) throw()
{
    this->errorCode             = errorCode; 
    this->errorMessage          = errorMessage;

    this->innerErrorCode     = innerErrorCode;
    this->innerErrorMessage  = innerErrorMessage;

    this->fileName              = fileName; 
    this->lineNo                = lineNo;
}



}}
