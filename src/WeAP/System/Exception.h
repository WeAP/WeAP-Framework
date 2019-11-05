#ifndef __WeAP_Exception_H__
#define __WeAP_Exception_H__


#include "Object.h"
#include "Defines.h"

namespace WeAP { namespace System {


/**
 * system exception
 * 
 * @author xzwang
 * @date 2018-05-09
 */
class Exception : public Object
{
public:
    static const int InvalidErrorCode = 0;
public:
    Exception(int errorCode, 
              const string& errorMessage) throw();


    Exception(int errorCode, 
              const string& errorMessage, 
              int innerErrorCode,
              const string& innerErrorMessage) throw();

    Exception(int errorCode, 
              const string& errorMessage, 
              const string& fileName, 
              int lineNo) throw();

    Exception(int errorCode, 
              const string& errorMessage, 
              int innerErrorCode,
              const string& innerErrorMessage, 
              const string& fileName, 
              int lineNo) throw();
    
    Exception(const Exception& other) throw();
    virtual ~Exception() throw();
    
    Exception& operator=(const Exception& other) throw();

protected:
    void Init(const Exception& other) throw();
    void Init(int errorCode, 
                   const string& errorMessage, 
                   int innerErrorCode = Exception::InvalidErrorCode,
                   const string& innerErrorMessage = "", 
                   const string& fileName = "", 
                   int lineNo = 0) throw();
private:
    Exception() throw();

public:
    int errorCode;
    string errorMessage;

    int innerErrorCode;
    string innerErrorMessage;

    string fileName; 
    int lineNo;
    
};


}}

#endif //__WeAP_Exception_H__
