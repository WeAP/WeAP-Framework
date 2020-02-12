#ifndef __WeAP_MutexList_H__
#define __WeAP_MutexList_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

using namespace WeAP::System;


namespace WeAP { namespace Thread {

template<T>
class MutexList: public Object
{
public:
    MutexList();
    virtual ~MutexList();


    void PushFront(T*);
    void PopFront();
    T* Front() const;

    void PushBack(T*);
    void PopBack();
    T* Back() const;

    void Clear();

    bool IsEmpty() const;
    size_t Size() const;

protected:
    std::list<T*> list;
    Mutex mutex;
};

}}

#endif

