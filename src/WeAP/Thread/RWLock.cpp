#include "RWLock.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

RWLock::RWLock()
{
    pthread_rwlock_init(&this->rwlock, NULL);

}

RWLock::~RWLock()
{
    pthread_rwlock_destroy(&this->rwlock);
}


void RWLock::RLock()
{
    int ret = pthread_rwlock_rdlock(&this->rwlock);
    if (ret != 0)
    {
        //cout << "lock throw " << ret << endl;
        throw Exception(Error::RWLock_RLock_Failed, "pthread_rwlock_rdlock failed");
    }
    //cout << "=============Locked" << endl;
}

void RWLock::WLock()
{
    int ret = pthread_rwlock_wrlock(&this->rwlock);
    if (ret != 0)
    {
        //cout << "lock throw " << ret << endl;
        throw Exception(Error::RWLock_WLock_Failed, "pthread_rwlock_wrlock failed");
    }
}

void RWLock::Unlock()
{
    int ret = pthread_rwlock_unlock(&this->rwlock);
    if (ret != 0)
    {
        //cout << "unlock throw " << ret << endl;
        throw Exception(Error::RWLock_Unlock_Failed, "pthread_rwlock_unlock failed");
    }
    //cout << "=============Unlocked" << endl;
}


}}

