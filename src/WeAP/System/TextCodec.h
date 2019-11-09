#ifndef __WeAP_TextCodec_H__
#define __WeAP_TextCodec_H__

#include "Object.h"


namespace WeAP { namespace System {


class TextCodec: public Object
{
private:
    TextCodec();
    
public:
    string UrlEncode(const string& str);
    string UrlDecode(const string& str);

protected:

};

}}

#endif //__WeAP_TextCodec_H__