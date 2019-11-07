#include "Util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <net/if.h>
#include "Exception.h"
#include "Error.h"

namespace WeAP { namespace System {


int Util::GetRandom(int min, int max)
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

string Util::GetLocalIpHex()
{
    string localIP = Util::GetLocalIp();
    in_addr_t lIp = inet_addr(localIP.c_str()) ;
    char szBuf[128] = {0};
    snprintf(szBuf,sizeof(szBuf),"%08x",lIp);
    return szBuf;
}

string Util::GetLocalIp()
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


bool Util::RegexMatch(const string& str, const string& pattern, int cflags)
{
    regex_t reg;
    int ret = regcomp(&reg, pattern.c_str(), cflags);
    if(ret != 0)
    {
        char errBuf[128] = {0};
        regerror(ret, &reg, errBuf, sizeof(errBuf) - 1);

        regfree(&reg);
        throw Exception(Error::RegexMatch_Failed, errBuf);        
    }

    regmatch_t regmatch[10];
    memset(regmatch,0,sizeof(regmatch));
    const int nmatch = 10;
    ret = regexec(&reg, str.c_str(), nmatch, regmatch, 0);
    if(ret == 0)
    {
        regfree(&reg);
        return true;
    }
    else if(ret == REG_NOMATCH)
    {
        regfree(&reg);
        return false;
    }
    else
    {
        char errBuf[128] = {0};
        regerror(ret, &reg, errBuf, sizeof(errBuf) - 1);

        regfree(&reg);
        throw Exception(Error::RegexMatch_Failed, errBuf);
    }

}

}}