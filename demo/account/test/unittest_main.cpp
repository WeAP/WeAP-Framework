
#include "gtest/gtest.h"
#include "Logger.h"
#include "stdinc.h"

#include "StringUtil.h"
#include "AccountManager.h"


using namespace WeAP::System;

int GTestRun(int argc, char *argv[])
{
    string confFile = "/home/xzwang/WeAP-Framework/unit_test/WeAP/conf/unittest.conf";
    //cout << confFile << endl;
    AccountManagerS::GetInstance()->Init(confFile);

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




