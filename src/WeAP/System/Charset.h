#ifndef __WeAP_Charset_H__
#define __WeAP_Charset_H__

#include "Object.h"


namespace WeAP { namespace System {


class Charset: public Object
{
private:
    Charset();

public:
    static const int GBK  = 1;  //GBK 编码
    static const int UTF8 = 2;  //UTF8 编码

public:

    static string GBKToUTF8(const string& str);
    static string UTF8ToGBK(const string& str);

    static string Convert(const string& str, int fromCode, int toCode);
    static string Convert(const string& fromstr, const string& from_code, const string& to_code);
    static int Convert(const char * pSrc, char * pDest, size_t& iDestLen, const char * from_code, const char * to_code);

    /**
     * UTF-8是一种多字节编码的字符集，表示一个Unicode字符时，它可以是1个至多个字节，在表示上有规律：
     * 1字节：0xxxxxxx
     * 2字节：110xxxxx 10xxxxxx
     * 3字节：1110xxxx 10xxxxxx 10xxxxxx
     * 4字节：11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
     */
    static bool IsUTF8(const string& str);

protected:
    static string GetCodeName(int code);

public:
    static bool IsUTF8(const string& str, bool includeNum, bool includeAlpha);


};

}}

#endif //__WeAP_Charset_H__