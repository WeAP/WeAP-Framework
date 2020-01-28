#ifndef __WeAP_Mutex_H__
#define __WeAP_Mutex_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

class Mutex: public Object
{
public:
    Mutex();
    virtual ~Mutex();

    void Lock();
    void TryLock();
    void Unlock();

protected:
    pthread_mutex_t* mutex;

};

}}

#endif

