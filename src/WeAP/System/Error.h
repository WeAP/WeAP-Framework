#ifndef ____ERROR_H_
#define ____ERROR_H_

#include "Object.h"

namespace WeAP { namespace System {


class Error : public Object
{
private:
    Error();

public:
    static const int Min = 10000;
    static const int Max = 19999;

    static void Init(int appCode); 
    static int ToAppError(int error);

public:
    static int appCode;  ///< app code

};

}}

#endif

