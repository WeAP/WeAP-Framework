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

    /**
     * 毫秒，ms
     */
    int GetCostMS();

    /**
     * 微秒，us
     */
    long GetCostUS();

    /**
     * 秒，s
     */
    int GetCostS();

    /**
     * 分，m
     */
    int GetCostM();
    
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

