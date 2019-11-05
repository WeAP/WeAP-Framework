
#include "Error.h"

namespace WeAP { namespace System {


int Error::appCode = 0;

void Error::Init(int appCode)
{
    Error::appCode = appCode;
}

int Error::ToAppError(int error)
{
    if ((error >= Error::Min && error <= Error::Max))
    {
        return Error::appCode * 100000 + error;
    }

    return error;    
}

}}


