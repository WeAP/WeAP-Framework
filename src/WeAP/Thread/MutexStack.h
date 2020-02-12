#ifndef __WeAP_Mutex_H__
#define __WeAP_Mutex_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

using namespace WeAP::System;


namespace WeAP { namespace Thread {

template<T>
class MutexStack: public Object
{
public:
    MutexStack();
    virtual ~MutexStack();

    void Push(T*);
    T* Pop();
    T* Top() const;
    void Clear();

    bool IsEmpty() const;
    size_t Size() const;

protected:
    std::stack<T*> stack;
    Mutex mutex;
};

}}

#endif

