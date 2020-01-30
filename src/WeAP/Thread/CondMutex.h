#ifndef __WeAP_CondMutex_H__
#define __WeAP_CondMutex_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

/**
CondMutex condMutex;

consumer thread:
condMutex.Lock();
while (x <= y)   //避免惊群效应
{
    condMutex.Wait();
}
condMutex.Unlock();

producer thread:
condMutex.Lock();
if (x > y)
{
    condMutex.Single(); //pthread_cond_signal 在多处理器上可能同时唤醒多个线程
}
condMutex.Unlock();

 */
class CondMutex: public Object
{
public:
    CondMutex();
    virtual ~CondMutex();

    void Lock();
    void Unlock();

    void Wait();
    void TimedWait(int sec, int nsec);
    void Signal();
    void Broadcast();

protected:    
    pthread_mutex_t mutex;
    pthread_cond_t cond;

};

}}

#endif

