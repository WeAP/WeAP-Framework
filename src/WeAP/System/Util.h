#ifndef __WeAP_Util_H__
#define __WeAP_Util_H__

#include "Object.h"

namespace WeAP { namespace Framework {

class Util//: public Object
{
private:
    Util();
    
public:
    static int GetRandomNumber(int min, int max);

};

}}


#endif //__WeAP_Util_H__