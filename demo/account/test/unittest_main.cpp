
#include "gtest/gtest.h"
#include "Logger.h"
#include "stdinc.h"

//#include <glog/logging.h>
//#include<gflags/flags.h>  
#include "StringUtil.h"

using namespace WeAP::System;

int GTestRun(int argc, char *argv[])
{
    string logDir = "/home/xzwang/WeAP-Framework/unit_test/WeAP/log";
    int logLevel = 2;
    int logSize =10;
    Logger::GetInstance()->Init(logDir,logLevel, logSize, "WeAP");
/*
    int i = 11;
    GLOG << "======aabc";

    ERROR("hellword===%d", i);
*/


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




