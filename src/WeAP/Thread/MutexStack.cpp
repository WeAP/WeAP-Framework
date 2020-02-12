#include "MutexStack.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

MutexStack::MutexStack()
{

}

MutexStack::~MutexStack()
{
}




void MutexStack::Push(T*)
{
    _mutex.lock();
    _threads.push(thread);
    _mutex.unlock();
}
T* MutexStack::Pop()
{
    _mutex.lock();
    Thread* top = _threads.top();
    _threads.pop();
    _mutex.unlock();
    return top;
}
T* MutexStack::Top() const
{
    return _threads.top();
}
void MutexStack::Clear()
{
    _mutex.lock();
    while (!_threads.empty()) {
        _threads.pop();
    }
    _mutex.unlock();
}

bool MutexStack::IsEmpty() const
{
    return _threads.empty();
}
size_t MutexStack::Size() const
{
    return _threads.size();
}


}}

