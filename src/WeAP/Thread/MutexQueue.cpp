#include "MutexQueue.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

MutexQueue::MutexQueue()
{

}

MutexQueue::~MutexQueue()
{
}




void MutexQueue::Push(T* val)
{
    this->mutex.lock();
    this->queue.push(val);
    this->mutex.unlock();
}
T* MutexQueue::Pop()
{
    this->mutex.lock();
    Thread* front = this->queue.front();
    this->queue.pop();
    this->mutex.unlock();
    return front;
}
T* MutexQueue::Front() const
{
    return this->queue.front();
}
void MutexQueue::Clear()
{
    this->mutex.lock();
    while (!this->queue.empty()) {
        this->queue.pop();
    }
    this->mutex.unlock();
}

bool MutexQueue::IsEmpty() const
{
    return this->queue.empty();
}
size_t MutexQueue::Size() const
{
    return this->queue.size();
}


}}

