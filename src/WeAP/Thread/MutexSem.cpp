#include "MutexSem.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {



MutexSem::MutexSem()
{


}

MutexSem::MutexSem(int64_t count)
{
    this->count = count;
}

MutexSem::~MutexSem()
{

}


void MutexSem::Wait()
{
    this->mutex.Lock();
    if (--this->count < 0) 
    {
        this->cond.Wait();
    }
    this->mutex.Unlock();
}
void MutexSem::Signal()
{
    this->mutex.Lock();
    if (++thsi->count <= 0) 
    {
        this->cond.Signal();
    }
    this->mutex.Unlock();
}

}}

