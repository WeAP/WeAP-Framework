#include "ProcessMutex.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

ProcessMutex::ProcessMutex()
{
    this->mutex = NULL;
    this->shmAddr = NULL;
}
ProcessMutex::~ProcessMutex()
{
    if (this->mutex != NULL)
    {
        pthread_mutex_destroy(this->mutex);
    }

    if (this->shmAddr != NULL)
    {
        int ret = shmdt(this->shmAddr);
        if (ret != 0)
        {
        }
    }
};

void ProcessMutex::Init(int shmkey)
{   
    int shmid = shmget(shmkey, sizeof(pthread_mutex_t), IPC_CREAT|IPC_EXCL|0666 );
    if (shmid > 0)
    {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);  
        pthread_mutexattr_destroy(&attr);
    }
    else if (shmid == -1)
    {
        shmid = shmget(shmkey, sizeof(pthread_mutex_t), IPC_CREAT|0666 );
    }

    //cout << "shmid:"<< shmid <<", size:" << sizeof(pthread_mutex_t) << endl;

    this->shmAddr = (void*)shmat(shmid, NULL, 0);
    this->mutex = reinterpret_cast<pthread_mutex_t*>(this->shmAddr);

}
void ProcessMutex::Lock()
{
    int ret = pthread_mutex_lock(this->mutex);
    if (ret != 0)
    {
        //cout << "lock throw " << ret << endl;
        throw Exception(Error::ProcessMutex_Lock_Failed, "pthread_mutex_lock failed");
    }
    //cout << "=============Locked" << endl;
}

void ProcessMutex::Unlock()
{
    int ret = pthread_mutex_unlock(this->mutex);
    if (ret != 0)
    {
        //cout << "unlock throw " << ret << endl;
        throw Exception(Error::ProcessMutex_Unlock_Failed, "pthread_mutex_unlock failed");
    }
    //cout << "=============Unlocked" << endl;
}





}}

