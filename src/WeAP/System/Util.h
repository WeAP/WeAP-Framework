#ifndef __WeAP_Util_H__
#define __WeAP_Util_H__

#include "Object.h"

namespace WeAP { namespace System {

class Util: public Object
{
private:
    Util();
    
public:
    static int GetRandomNumber(int min, int max);

    static string GetLocalIpHex();
    static string GetLocalIp();

    /**
     * @brief regex match
     * 
     * @param str 
     * @param pattern 
     * @param cflags 有如下4个值或者是它们或运算(|)后的值：
     * REG_EXTENDED 以功能更加强大的扩展正则表达式的方式进行匹配。
     * REG_ICASE 匹配字母时忽略大小写。
     * REG_NOSUB 不用存储匹配后的结果。
     * REG_NEWLINE 识别换行符，这样'$'就可以从行尾开始匹配，'^'就可以从行的开头开始匹配。
     */
    static bool RegexMatch(const string& str, const string& pattern, int cflags = REG_EXTENDED);

};

}}


#endif //__WeAP_Util_H__