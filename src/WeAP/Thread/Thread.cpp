#include "Thread.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace Thread {

void* Thread::StartRoutine(void* arg)
{
    Thread* thread = (Thread*) arg;
    thread->Run();
    return NULL;
}

Thread::Thread(bool detached)
{
    this->tid = 0;
    this->isRunning = false;
    this->detached = detached;
    int ret = pthread_attr_init( &this->attr );
    if ( 0 != ret )
    {
        ERROR("pthread_attr_init failed");
        return;
    }
    ret = pthread_attr_setscope(&this->attr, PTHREAD_SCOPE_PROCESS);  //用户级线程, 线程与它所在的进程中的其他线程竞争处理器资源
    //ret = pthread_attr_setscope(&this->attr, PTHREAD_SCOPE_SYSTEM); //内核级线程, 线程在全系统的范围内竞争处理器资源

    if (this->detached)
    {
        ret = pthread_attr_setdetachstate( &this->attr, PTHREAD_CREATE_DETACHED );
    }
    else
    {
        ret = pthread_attr_setdetachstate( &this->attr, PTHREAD_CREATE_JOINABLE );
    }
    

}

Thread::~Thread()
{
    pthread_kill(this->tid, 0);
    if (this->detached)
    {
        pthread_attr_destroy( &this->attr );
    }
}


void Thread::Start()
{
    this->isRunning = true;

    int ret = pthread_create( &this->tid, &this->attr, Thread::StartRoutine, (void*)this );
    if ( ret != 0)
    {
        ERROR("Start a new thread failed, ret:%d", ret);
        return -1;
    }


}

void Thread::Stop()
{
    this->Cancel();
    this->Join();
}

void Thread::Resume()
{

}

bool Thread::IsJoinable()
{
    if (this->detached)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

void Thread::Join()
{
    if (this->tid == 0)
    {
        return;
    }

    if (!this->IsJoinable())
    {
        return;
    }

    int ret = pthread_join(this->tid, NULL);
    if (ret != 0)
    {
        ERROR("Join the thread failed, tid=%u", his->tid);
        return;
    }

    INFO("Join the thread succ, tid=%u", this->tid);
}

void Thread::Detach()
{
    pthread_detach(this->tid);
}




void Thread::Cancel()
{
    this->isRunning = false;
    int ret = pthread_cancel(this->tid);
}

void Thread::TestCancel()
{
    pthread_testcancel();
}

void Thread::Exit()
{
    this->isRunning = false;
    pthread_exit(NULL);
}

void Thread::SetPriority(int p)
{
    int policy;
    sched_param sp;
    pthread_getschedparam(this->tid, &policy, &sp);
    sp.sched_priority = p;
    pthread_setschedparam(this->tid, policy, reinterpret_cast<const struct sched_param*>(&sp));
}

int Thread::GetPriority()
{
    int policy;
    sched_param sp;
    pthread_getschedparam(this->tid, &policy, &sp);
    return sp.sched_priority;
}

void Thread::SetConcurrency(int level)
{
    pthread_setconcurrency(level);
}

int Thread::GetConcurrency()
{
    return pthread_getconcurrency();
}

State Thread::GetState()
{
    return this->state;
}

}}

