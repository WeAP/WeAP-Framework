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

    Account account;
    account.accountId = time(NULL);
    account.balance = 1;
    account.status = Account::Normal;
    account.createTime = DateTime().ToDateTimeString();
    account.modifyTime = DateTime().ToDateTimeString();

    dao.Insert(account);

    Account accountDB;
    dao.Query(account.accountId, accountDB);


    EXPECT_EQ(true, account.Equals(accountDB));

}

void AccountDAOTest::TestUpdate()
{
    string confFile = "/home/xzwang/WeAP-Framework/unit_test/WeAP/conf/unittest.conf";
    INIConfig config;
    config.Init(confFile);

    AccountDAO dao;
    dao.Init(config, "Account");

    Account account;
    account.accountId = time(NULL) + 1;
    account.balance = 1;
    account.status = Account::Normal;
    account.createTime = DateTime().ToDateTimeString();
    account.modifyTime = DateTime().ToDateTimeString();

    dao.Insert(account);

    Account accountDB;
    dao.Query(account.accountId, accountDB);
    accountDB.balance += 1;

    dao.Update(accountDB);

    Account accountDB2;
    dao.Query(account.accountId, accountDB2);

    EXPECT_EQ(false, account.Equals(accountDB2));
    EXPECT_EQ(true, accountDB.Equals(accountDB2));

}


TEST_F(AccountDAOTest, TestInsert)
{
    TestInsert();
}


TEST_F(AccountDAOTest, TestUpdate)
{
    TestUpdate();
}