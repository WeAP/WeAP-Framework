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

    void Push(T val)
    {
        std::lock_guard<std::mutex> lock(this->mutex);

        this->stack.push(val);
    };

    T Pop()
    {
        std::lock_guard<std::mutex> lock(this->mutex);

        T top = this->stack.top();
        this->stack.pop();

        return top;
    };

    const T Top() const
    {
        return this->stack.top();
    };

    void Clear()
    {
        std::lock_guard<std::mutex> lock(this->mutex);

        while (!this->stack.empty()) 
        {
            this->stack.pop();
        }

    };

    bool IsEmpty() 
    {
        std::lock_guard<std::mutex> lock(this->mutex);

        return this->stack.empty();
    };

    size_t Size()
    {
        std::lock_guard<std::mutex> lock(this->mutex);
        return this->stack.size();
    };

protected:
    std::stack<T> stack;
    std::mutex mutex;
};

}}

#endif

