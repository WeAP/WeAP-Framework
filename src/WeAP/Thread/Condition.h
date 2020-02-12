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
    condMutex.Signal(); //pthread_cond_signal 在多处理器上可能同时唤醒多个线程
}
condMutex.Unlock();


使用场景：
accept惊群
epoll惊群
nginx惊群
线程池惊群
 */
class CondMutex: public Object
{
public:
    Condition(Mutex* mutex);
    virtual ~CondMutex();


    void Wait();
    void TimedWait(int sec, int nsec);
    void Signal();
    void Broadcast();


protected:
    pthread_cond_t cond;
    pthread_mutex_t* mutex;
};

}}

#endif

