#include "ThreadPool.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {



ThreadPool::ThreadPool(int threadCount)
{
    this->threadCount = threadCount;
    for (size_t i = 0; i < this->threadCount; i++)
    {
        Thread* worker = new Worker();
        this->threadList.push_back(worker);
    }
}

ThreadPool::~ThreadPool()
{
    while (!this->busyThreads.is_empty()) 
    {
        this->MoveBusyToIdle();
    }

    this->Stop();



    for (size_t i = 0; i < this->threadList.size(); i++)
    {
        delete this->threadList[i];
    }

    this->threadList.clear();
}

bool ThreadPool::AddWorker(Thread * worker)
{
    this->allThreads.push_back(worker);
    this->idleThreads.push(worker);
}
bool ThreadPool::AddTask(Task *, void *arg)
{
    this->tasks.enter(task);
    _task_args[task] = arg;
}

void ThreadPool::Run()
{
    while (!_tasks.is_empty()) 
    {
        while (_idle_threads.is_empty()) 
        {
            retrieve_busy_to_idle();
        }

        Task *task = _tasks.leave();
        Worker *worker = dynamic_cast<Worker *>(_idle_threads.pop());
        if (worker == nullptr) 
        {
            continue;
        }

        task->set_executor(worker);
        worker->set_task(task, _task_args[task].first);
        _busy_threads.enter(worker);

        worker->resume();
    }
}



void ThreadPool::Stop()
{
    while (!this->busyThreads.IsEmpty()) 
    {
        this->MoveBusyToIdle();
    }

    while (!this->idleThreads.is_empty()) 
    {
        Thread *worker = this->idleThreads.pop();
        worker->Stop();
    }

    for (size_t i = 0; i < this->threadList.size(); i++)
    {
        this->threadList[i].Join();
    }
    
}

void ThreadPool::MoveBusyToIdle()
{
    for (auto &thread : this->allThreads) 
    {
        if (this->busyThreads.Exist(thread)) 
        {
            if (thread->GetState() == Thread::State::Suspended) 
            {
                this->busyThreads.remove(thread);
                this->idleThreads.push(thread);
            }
        }
    }
}

}}

