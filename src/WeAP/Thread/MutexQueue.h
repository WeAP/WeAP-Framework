#ifndef __WeAP_MutexQueue_H__
#define __WeAP_MutexQueue_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

using namespace WeAP::System;


namespace WeAP { namespace Thread {

template<T>
class MutexQueue: public Object
{
public:
    MutexQueue();
    virtual ~MutexQueue();

    void Enter(T* val);
    T* Leave();

    void Push(T* val);
    T* Pop();

    T* Front() const;

    void Clear();

    bool IsEmpty() const;
    size_t Size() const;

protected:
    std::queue<T*> queue;
    Mutex mutex;
};

}}

#endif

