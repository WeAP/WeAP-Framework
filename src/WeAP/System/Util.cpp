#include "Util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <net/if.h>

namespace WeAP { namespace System {


int Util::GetRandomNumber(int min, int max)
{ 
    int fd = ::open("/dev/urandom",O_RDONLY);
    unsigned int randNum = 0;
    if ( fd >= 0 )
    {
        ::read(fd, &randNum, sizeof(randNum));
        ::close(fd); 
    }
    if ( randNum == 0 )
    {
        randNum = (unsigned int)::random();
    }
    
    return randNum % (max - min + 1) + min;

}

string Util::GetEth1IP()
{
    return Util::GetLocalIP("eth1");
}

string Util::GetLocalIP(const string& interfaceName)
{
    char szIP[64] = {0};
    int inet_sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct ifreq ifr;
    strncpy(ifr.ifr_name, interfaceName.c_str(), sizeof(ifr.ifr_name) - 1);
    ifr.ifr_name[sizeof(ifr.ifr_name) - 1] = '\0';

    if (!ioctl(inet_sock, SIOCGIFADDR, &ifr))
    {
        inet_ntop(AF_INET, &(((struct sockaddr_in*)(&ifr.ifr_addr))->sin_addr), szIP, sizeof(szIP));
    }

    close(inet_sock);
    
    return szIP;
}

string Util::GetLocalHostIpHex()
{
    string localIP = Util::GetLocalHostIp();
    in_addr_t lIp = inet_addr(localIP.c_str()) ;
    char szBuf[128] = {0};
    snprintf(szBuf,sizeof(szBuf),"%08x",lIp);
    return szBuf;
}

string Util::GetLocalHostIp()
{
    int fd, intrface;
    char szBuf[64] = {"255.255.255.255"};
    struct ifreq buf[16];
    struct ifconf ifc;

    if((fd=socket (AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
        ifc.ifc_len = sizeof buf;
        ifc.ifc_buf = (caddr_t) buf;
        if (!ioctl(fd, SIOCGIFCONF, (char*)&ifc))
        {
            intrface = ifc.ifc_len / sizeof(struct ifreq);
            while(intrface-- > 0)
            {
                if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface])))
                {
                    inet_ntop(AF_INET, &(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr), szBuf, sizeof(szBuf));
                    break;
                }
            }
        }
        close (fd);
    }

    return szBuf;
}


int Util::RegexMatch(const string& strSrc, const string& strRegular, string& strErrmsg, int cflags)
{
    int iRet = -1;
    regex_t reg;
    char ebuf[128] = {0};
    regmatch_t regmatch[10];
    memset(regmatch,0,sizeof(regmatch));
    const int nmatch = 10;
    int iSuccess = 2;
    
    iRet = regcomp(&reg, strRegular.c_str(), cflags);
    if(iRet != 0)
    {
        regerror(iRet, &reg, ebuf, sizeof(ebuf) - 1);
        strErrmsg = ebuf;
        
        regfree(&reg);
        return 2;
    }

    iRet = regexec(&reg, strSrc.c_str(), nmatch, regmatch, 0);
    if(iRet == 0)
    {
        iSuccess = 0;
    }
    else if(iRet == REG_NOMATCH)
    {
        iSuccess = 1;
    }
    else
    {
        regerror(iRet, &reg, ebuf, sizeof(ebuf) - 1);
        strErrmsg = ebuf;
        iSuccess = 2;
    }
    regfree(&reg);
    return iSuccess;
}


string Util::GenerateMsgNo(int appCode)
{    
    char buf[32] = {0};
    static unsigned int seq = 0;
    static int proc = getpid();
    snprintf(buf, sizeof(buf), "%04d%05d%010u%010u", appCode, proc, (int)time(NULL), seq++);
    
    return string(buf);
    
}

string Util::FenToYuan(long long int fen)
{
    if (fen < 0)
    {
        return "";
    }

    char yuan[128] = {0};
    long long int quo = fen / 100;
    int mod = fen % 100;
    snprintf(yuan, sizeof(yuan), "%lld.%02d", quo, mod);
    
    return yuan;
}

}}