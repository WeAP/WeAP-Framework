#include "Mutex.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

Mutex::Mutex()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);

    pthread_mutex_init(&this->mutex, &attr);

}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&this->mutex);
}


void Mutex::Lock()
{
    int ret = pthread_mutex_lock(&this->mutex);
    if (ret != 0)
    {
        //cout << "lock throw " << ret << endl;
        throw Exception(Error::Mutex_Lock_Failed, "pthread_mutex_lock failed");
    }
    //cout << "=============Locked" << endl;
}

void Mutex::TryLock()
{
    int ret = pthread_mutex_trylock(&this->mutex);
    if (ret != 0)
    {
        //cout << "lock throw " << ret << endl;
        throw Exception(Error::Mutex_TryLock_Failed, "pthread_mutex_lock failed");
    }
}

void Mutex::Unlock()
{
    int ret = pthread_mutex_unlock(&this->mutex);
    if (ret != 0)
    {
        //cout << "unlock throw " << ret << endl;
        throw Exception(Error::Mutex_Unlock_Failed, "pthread_mutex_unlock failed");
    }
    //cout << "=============Unlocked" << endl;
}


}}

