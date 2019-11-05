#ifndef __WeAP_Error_H__
#define __WeAP_Error_H__

#include "Object.h"

namespace WeAP { namespace System {


class Error : public Object
{
private:
    Error();

public:
    static const int Min = 10000;
    static const int Max = 19999;


    static const int ERR_OBJECT_LIST_GET_OUT_OF_RANGE = 10000;
    
    static const int ERR_FILE_UTIL_OPEN_FAILED        = 10001;




    static void Init(int appCode); 
    static int ToAppError(int error);

public:
    static int appCode;  ///< app code

};

}}

#endif

