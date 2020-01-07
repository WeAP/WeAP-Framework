#ifndef __WeAP_ProcessMutex_H__
#define __WeAP_ProcessMutex_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

class ProcessMutex: public Object
{
public:
    ProcessMutex();
    virtual ~ProcessMutex();

    void Init(int shmkey);
    void Lock();    
    void Unlock();

protected:
    pthread_mutex_t* mutex;
    void* shmAddr;    
};

}}

#endif

