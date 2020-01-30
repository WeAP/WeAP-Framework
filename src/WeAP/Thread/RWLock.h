#ifndef __WeAP_RWLock_H__
#define __WeAP_RWLock_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

class RWLock: public Object
{
public:
    RWLock();
    virtual ~RWLock();

    void RLock();
    void WLock();
    void Unlock();

protected:
    pthread_rwlock_t rwlock;

};

}}

#endif

