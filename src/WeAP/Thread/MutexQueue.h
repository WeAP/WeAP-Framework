#ifndef __WeAP_MutexQueue_H__
#define __WeAP_MutexQueue_H__

#include <sys/shm.h>
#include "Object.h"
#include <queue>
#include <mutex>

using namespace WeAP::System;


namespace WeAP { namespace Thread {

/**
 * 
 * https://cloud.tencent.com/developer/article/1433745 
 */

template<class T> 
class MutexQueue: public Object
{
public:
    MutexQueue(){};
    virtual ~MutexQueue(){};

    void Push(T val)  //入队
    {
        std::lock_guard<std::mutex> lock(this->mutex);

        this->queue.push(val);
    };

    T Pop()  // 出队
    {
        std::lock_guard<std::mutex> lock(this->mutex);

        T front = this->queue.front();
        this->queue.pop();

        return front;
    };

    const T Front() const
    {
        return this->queue.front();
    };

    const T Back() const
    {
        return this->queue.back();
    };

    void Clear()
    {
        //std::lock_guard<std::mutex> lock(this->mutex);

        while (!this->queue.empty()) 
        {
            this->queue.pop();
        }

    };

    bool IsEmpty()
    {
        std::lock_guard<std::mutex> lock(this->mutex);

        return this->queue.empty();
    };
    
    size_t Size()
    {
        std::lock_guard<std::mutex> lock(this->mutex);
        return this->queue.size();
    };

protected:
    std::queue<T> queue;
    std::mutex mutex;
    

};

}}

#endif

