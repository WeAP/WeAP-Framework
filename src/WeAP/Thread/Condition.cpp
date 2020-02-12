#include "CondMutex.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

CondMutex::CondMutex(Mutex* mutex)
{
    this->mutex = mutex->mutex;
    pthread_cond_init(&this->cond, NULL);
}

CondMutex::~CondMutex()
{
    pthread_cond_destroy(&this->cond);
    if (this->mutex != NULL)
    {
        this->mutex = NULL;
    }
}



void CondMutex::Wait()
{
    int ret = pthread_cond_wait(&this->cond, &this->mutex);
    if (ret != 0)
    {
        //cout << "lock throw " << ret << endl;
        throw Exception(Error::CondMutex_Lock_Failed, "pthread_mutex_lock failed");
    }
    //cout << "=============Locked" << endl;
}

void CondMutex::TimedWait(int sec, int nsec)
{
    struct timespec ts;

    ts.tv_sec = time(NULL) + sec;
    ts.tv_nsec = nsec;

    int ret = pthread_cond_timedwait(&this->cond, &this->mutex, &ts);
    if (ret == 0)
    {
        return ;
    }
    else if (ret != ETIMEDOUT)
    {
        ERROR("pthread_cond_timedwait, ret:%d, err:%s", ret, strerror(errno))
        throw Exception(Error::CondMutex_TimedWait_Failed, "pthread_cond_timedwait failed");
    }
    else if (ret == ETIMEDOUT)
    {
        return ;
    }

}

void CondMutex::Signal()
{
    int ret = pthread_cond_signal(&this->cond);
    if (ret != 0)
    {
        //cout << "unlock throw " << ret << endl;
        throw Exception(Error::CondMutex_Signal_Failed, "pthread_mutex_unlock failed");
    }
    //cout << "=============Unlocked" << endl;
}

void CondMutex::Broadcast()
{
    int ret = pthread_cond_broadcast(&this->cond);
    if (ret != 0)
    {
        throw Exception(Error::CondMutex_Broadcast_Failed, "pthread_mutex_unlock failed");
    }
}

}}

