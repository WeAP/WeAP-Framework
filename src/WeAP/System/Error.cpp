
#include "Error.h"

namespace WeAP { namespace System {


int Error::appCode = 0;

void Error::Init(int appCode)
{
    Error::appCode = appCode;
}

int Error::ToAppError(int error)
{
    if (Error::appCode > 0)
    {
        return Error::appCode * 100000 + error;
    }

    return error;    
}

}}


