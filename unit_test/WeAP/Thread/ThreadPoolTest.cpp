#include "ThreadPoolTest.h"
#include "DateTime.h"
//#include "ThreadPool.h"

//using namespace WeAP::Thread;
using namespace WeAP::System;


class LoopTask: public Task
{
public:
    LoopTask()
    :Task("LoopTask")
    {

    };
    virtual ~LoopTask(){};

    virtual void Run(void* arg)
    {
        int* count = (int*) arg;
        for(int i = 0; i < *count; i++)
        {
            cout << "loop " << i << endl;
            sleep(1);
        }
    };


};





ThreadPoolTest::ThreadPoolTest()
{

}

ThreadPoolTest::~ThreadPoolTest()
{

}


void ThreadPoolTest::TestRun()
{

    //ThreadPool pool(10);

    //int loopCount = 20;

    //pool.AddTask(new LoopTask(), &loopCount);

    //cout << val << endl;

    //EXPECT_EQ(value, val);

}

TEST_F(ThreadPoolTest, TestRun)
{
    TestRun();
}

