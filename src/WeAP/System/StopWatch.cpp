
#include "StopWatch.h"

namespace WeAP { namespace System {


StopWatch::StopWatch()
{
    this->startTime.tv_sec = 0;
    this->startTime.tv_usec = 0;
    this->stopTime.tv_sec = 0;
    this->stopTime.tv_usec = 0;
    
    this->isRunning = false;
    this->Start();
}
StopWatch::~StopWatch()
{
}

int StopWatch::GetCostMS()
{
    if (this->isRunning)
    {
        this->Stop();
    }
    
    double elapsed = (this->stopTime.tv_sec - this->startTime.tv_sec) * 1000.0 +
                        (this->stopTime.tv_usec - this->startTime.tv_usec)/1000.0;
    return (int)elapsed;
}

long StopWatch::GetCostUS()
{   
    if (this->isRunning)
    {
        this->Stop();
    }
        
    double elapsed = (this->stopTime.tv_sec - this->startTime.tv_sec) * 1000.0 * 1000.0 +
                        (this->stopTime.tv_usec - this->startTime.tv_usec);
    return (long)elapsed;
}

int StopWatch::GetCostS()
{
    if (this->isRunning)
    {
        this->Stop();
    }
        
    return this->stopTime.tv_sec - this->startTime.tv_sec;
}

int StopWatch::GetCostM()
{
    if (this->isRunning)
    {
        this->Stop();
    }
            
    return (this->stopTime.tv_sec - this->startTime.tv_sec) / 60;
}

void StopWatch::Start()
{
    ::gettimeofday(&this->startTime, NULL);
    this->isRunning = true;
}

void StopWatch::Stop()
{
    ::gettimeofday(&this->stopTime, NULL);
    this->isRunning = false;
}

bool StopWatch::IsRunning()
{
    return this->isRunning;
}

}}


