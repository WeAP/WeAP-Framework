#ifndef __WeAP_MutexSem_H__
#define __WeAP_MutexSem_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

#include "Condition.h"
#include "Mutex.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

/**
 * 
 */
class MutexSem: public Object
{
public:
    MutexSem();
    explicit MutexSem(int64_t count);
    virtual ~MutexSem();

    void Wait();
    void Signal();

protected:
    int64_t count;
    Condition cond;
    Mutex mutex;

};

}}

#endif

