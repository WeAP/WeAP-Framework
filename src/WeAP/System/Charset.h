#ifndef __WeAP_Charset_H__
#define __WeAP_Charset_H__

#include "Object.h"


namespace WeAP { namespace System {


class Charset: public Object
{
private:
    Charset();
    
public:
    static bool IsUTF8(const string& str);
    static bool IsUTF8(const char* str, size_t size);


};

}}

#endif //__WeAP_Charset_H__