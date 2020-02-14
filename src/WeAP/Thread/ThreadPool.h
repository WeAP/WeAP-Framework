#ifndef __WeAP_ThreadPool_H__
#define __WeAP_ThreadPool_H__

#include <sys/shm.h>
#include <pthread.h>
#include "Object.h"
#include "Thread.h"
#include "MutexStack.h"
#include "MutexQueue.h"


using namespace WeAP::System;

namespace WeAP { namespace Thread {

class Task
{
public:
    Task(const string& taskName)
    {
        this->taskName = taskName;
    };
    virtual ~Task()
    {
    };

    virtual void Run(void* arg) = 0;

protected:
    string taskName;

};


class Worker: public Thread
{
public:
    Worker(){};
    virtual ~Worker(){};

    virtual void Run()
    {
        if (this->task != NULL)
        {
            this->task->Run(this->task_arg);
        }
    }

    void SetTask(Task *task, void *arg=nullptr) 
    { 
        this->task = task; 
        this->task_arg = arg; 
    }
protected:
    Task* task;
    void* task_arg;
};



/**
 * https://github.com/oshynsong/tp4cpp
 * https://github.com/lizhenghn123/zl_threadpool
 */
class ThreadPool: public Object
{
public:
    int MaxThreadCount = 10;
    int MaxTaskCount = 15;
public:
    ThreadPool(int threadCount);
    virtual ~ThreadPool();

    void AddWorker(Thread* worker);
    void AddTask(Task *, void *arg = NULL);

    void Run();

    void Stop();

protected:
    void MoveBusyToIdle();

protected:
    int threadCount;
    vector<Thread*> allThreads;
    vector<Task*> taskList;

    MutexStack<Thread> idleThreads;
    MutexQueue<Thread> busyThreads;

};

}}

#endif

