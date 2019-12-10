#include "AccountDAOTest.h"
#include "Account.h"
#include "AccountDAO.h"
#include "INIConfig.h"
#include "DateTime.h"

using namespace WeAP::System;

AccountDAOTest::AccountDAOTest()
{
}

AccountDAOTest::~AccountDAOTest()
{

}

void AccountDAOTest::TestInsert()
{
    string confFile = "/home/xzwang/WeAP-Framework/unit_test/WeAP/conf/unittest.conf";
    INIConfig config;
    config.Init(confFile);

    AccountDAO dao;
    dao.Init(config, "Account");

    try
    {
        Account account;
        account.accountId = time(NULL);
        account.balance = 1;
        account.status = Account::Normal;
        account.createTime = DateTime().ToDateTimeString();
        account.modifyTime = DateTime().ToDateTimeString();

        dao.Insert(account);

        //dao.Query(1, account);        
    }
    catch(const Exception& ex)
    {
        std::cerr << ex.errorMessage << '\n';
    }    
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cout << "unknown error"  << '\n';
    }





    
    

}


TEST_F(AccountDAOTest, TestInsert)
{
    TestInsert();
}
