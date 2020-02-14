#ifndef __WeAP_MutexStack_H__
#define __WeAP_MutexStack_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"
#include <stack>
#include <mutex>

using namespace WeAP::System;


namespace WeAP { namespace Thread {

template<class T>
class MutexStack: public Object
{
public:
    MutexStack(){};
    virtual ~MutexStack(){};

    void Push(T* val)
    {
        this->mutex.lock();
        this->stack.push(val);
        this->mutex.unlock();
    };

    T* Pop()
    {
        this->mutex.lock();
        T* top = this->stack.top();
        this->stack.pop();
        this->mutex.unlock();
        return top;
    };

    T* Top() const
    {
        return this->stack.top();
    };

    void Clear()
    {
        this->mutex.lock();
        while (!this->stack.empty()) 
        {
            this->stack.pop();
        }
        this->mutex.unlock();
    };

    bool IsEmpty() const
    {
        return this->stack.empty();
    };
    
    size_t Size() const
    {
        return this->stack.size();
    };

protected:
    std::stack<T*> stack;
    std::mutex mutex;
};

}}

#endif

