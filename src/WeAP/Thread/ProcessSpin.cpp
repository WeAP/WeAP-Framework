#include "ProcessSpin.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

ProcessSpin::ProcessSpin()
{
    this->spinlock = NULL;
    this->shmAddr = NULL;
};
ProcessSpin::~ProcessSpin()
{
    if (this->spinlock != NULL)
    {
        pthread_spin_destroy(this->spinlock);
    }

    if (this->shmAddr != NULL)
    {
        int ret = shmdt(this->shmAddr);
        if (ret != 0)
        {
        }
    }
};


void ProcessSpin::Init(int shmkey)
{   
    int shmid = shmget(shmkey, sizeof(pthread_spinlock_t), IPC_CREAT|IPC_EXCL|0666 );
    if (shmid > 0)
    {
        this->shmAddr = (void*)shmat(shmid, NULL, 0);
        this->spinlock = reinterpret_cast<pthread_spinlock_t*>(this->shmAddr);
        
        pthread_spin_init(this->spinlock, PTHREAD_PROCESS_SHARED);

    }
    else if (shmid == -1)
    {
        shmid = shmget(shmkey, sizeof(pthread_spinlock_t), IPC_CREAT|0666 );

        this->shmAddr = (void*)shmat(shmid, NULL, 0);
        this->spinlock = reinterpret_cast<pthread_spinlock_t*>(this->shmAddr);
    }

    //cout << "shmid:"<< shmid <<", size:" << sizeof(pthread_spinlock_t) << endl;
}
void ProcessSpin::Lock()
{
    int ret = pthread_spin_lock(this->spinlock);
    if (ret != 0)
    {
        //cout << "lock throw " << ret << endl;
        throw Exception(Error::ProcessSpin_Lock_Failed, "pthread_spin_lock failed");
    }
    //cout << "=============Locked" << endl;
}

void ProcessSpin::Unlock()
{
    int ret = pthread_spin_unlock(this->spinlock);
    if (ret != 0)
    {
        //cout << "unlock throw " << ret << endl;
        throw Exception(Error::ProcessSpin_Unlock_Failed, "pthread_spin_unlock failed");
    }
    //cout << "=============Unlocked" << endl;
}

}}

