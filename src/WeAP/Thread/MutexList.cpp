#include "MutexList.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

MutexList::MutexList()
{

}

MutexList::~MutexList()
{
}


void MutexList::PushFront(T*)
{

}

void MutexList::PopFront()
{

}

T* MutexList::Front() const
{

}


void MutexList::PushBack(T*)
{

}

void MutexList::PopBack()
{

}

T* MutexList::Back() const
{

}


void MutexList::Clear()
{
    _mutex.lock();
    while (!_threads.empty()) {
        _threads.pop();
    }
    _mutex.unlock();
}

bool MutexList::IsEmpty() const
{
    return _threads.empty();
}
size_t MutexList::Size() const
{
    return _threads.size();
}


}}

