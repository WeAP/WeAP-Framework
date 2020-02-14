#include "ThreadPool.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {



ThreadPool::ThreadPool(int threadCount)
{
    this->threadCount = threadCount;
    for (int i = 0; i < this->threadCount; i++)
    {
        Thread* worker = new Worker();
        this->allThreads.push_back(worker);
    }
}

ThreadPool::~ThreadPool()
{
    while (!this->busyThreads.IsEmpty()) 
    {
        this->MoveBusyToIdle();
    }

    this->Stop();



    for (size_t i = 0; i < this->allThreads.size(); i++)
    {
        delete this->allThreads[i];
    }

    this->allThreads.clear();
}

void ThreadPool::AddWorker(Thread* worker)
{
    this->allThreads.push_back(worker);
    //todo this->idleThreads.Push(worker);

}
void ThreadPool::AddTask(Task * task, void *arg)
{
    //this->taskList.push_back(task);
    //_task_args[task] = arg;
}

void ThreadPool::Run()
{
    /*
    while (!this->taskList.IsEmpty()) 
    {
        while (_idle_threads.IsEmpty()) 
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
    */
}



void ThreadPool::Stop()
{
    while (!this->busyThreads.IsEmpty()) 
    {
        this->MoveBusyToIdle();
    }

    while (!this->idleThreads.IsEmpty()) 
    {
        Thread *worker = this->idleThreads.Pop();
        worker->Stop();
    }

    for (size_t i = 0; i < this->allThreads.size(); i++)
    {
        this->allThreads[i]->Join();
    }
    
}

void ThreadPool::MoveBusyToIdle()
{
    for (auto &thread : this->allThreads) 
    {
        //if (this->busyThreads.Exist(thread)) 
        {
            if (thread->GetState() == Thread::State::Suspended) 
            {
                //this->busyThreads.Leave(thread);
                this->idleThreads.Push(thread);
            }
        }
    }
}

}}

