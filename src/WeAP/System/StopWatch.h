#ifndef __WeAP_StopWatch_H__
#define __WeAP_StopWatch_H__

#include <string>
#include <sys/time.h>
#include <unistd.h>
#include "Object.h"

namespace WeAP { namespace System {


/**
 * 秒表，用于计时
 * @author xzwang
 */
class StopWatch : public Object
{
public:
    StopWatch();
    virtual ~StopWatch();

    int GetCostMS();  ///< get cost time by millisecond
    long GetCostUS(); ///< get cost time by microsecond
    int GetCostS();   ///< get cost time by second
    int GetCostM();   ///< get cost time by minute
    
protected:
    void Start();    
    void Stop();
    bool IsRunning();

protected:        
    struct timeval startTime;
    struct timeval stopTime;
    bool isRunning;
};

}}

#endif 

