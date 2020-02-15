#ifndef __WeAP_Thread_H__
#define __WeAP_Thread_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

class Thread: public Object
{
public:
    enum State 
    {
        Init = 0,
        Started = 1,
        Running = 2,
        Suspended = 3,
        Cancelled,
    };
protected:
    static void* StartRoutine(void* arg);

public:
    Thread(bool detached = false);
    virtual ~Thread();

    void Start();
    virtual void Run() = 0;
    void Stop();

    void Resume();
    bool IsJoinable();
    
    void Join();  //等待线程直至退出, 调用pthread_join的线程会阻塞，直到指定的线程返回
    //等待线程退出或者超时
    void Join(unsigned long millisTime);

    void Detach();

    void Cancel();
    void TestCancel();

    void Exit();

    void SetPriority(int p);
    int GetPriority();

    void SetConcurrency(int level);
    int GetConcurrency();

    pthread_t GetTid() { return this->tid; };
    Thread::State GetState();

protected:
    pthread_t tid;
    pthread_attr_t attr;
    State state;

    bool detached;

};

}}

#endif

