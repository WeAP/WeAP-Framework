#include "Util.h"
#include "stdinc.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 


namespace WeAP { namespace Framework {


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

}}