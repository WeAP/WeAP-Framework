#ifndef __WeAP_ProcessSpin_H__
#define __WeAP_ProcessSpin_H__

#include <sys/shm.h>
#include <pthread.h>

namespace WeAP { namespace Thread {

class ProcessSpin
{
public:
    ProcessSpin();
    virtual ~ProcessSpin();
    
    void Init(int shmkey);
    void Lock();
    void Unlock();

protected:
    pthread_spinlock_t* spinlock;
    void* shmAddr;
};


}}

#endif

