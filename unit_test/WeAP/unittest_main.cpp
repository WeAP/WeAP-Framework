
#include "gtest/gtest.h"
#include "Logger.h"
#include "stdinc.h"



int GTestRun(int argc, char *argv[])
{
    try
    {
        ::testing::InitGoogleTest(&argc, argv);    
        return RUN_ALL_TESTS();
    }
    catch(...)
    {
        cout << "unknown error" << endl;
    }

    return -1;

}


int main(int argc, char *argv[]) 
{
    return ::GTestRun(argc, argv); 

}




