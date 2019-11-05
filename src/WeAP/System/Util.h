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

    static string GetEth1IP();
    static string GetLocalIP(const string& interfaceName);

    static string GetLocalHostIpHex();
    static string GetLocalHostIp();

    static int RegexMatch(const string& strSrc, const string& strRegular, string& strErrmsg, int cflags = REG_EXTENDED);

    static string GenerateMsgNo(int appCode = 0);

    static string FenToYuan(long long int fen);
};

}}


#endif //__WeAP_Util_H__