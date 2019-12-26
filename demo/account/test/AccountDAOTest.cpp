#include "AccountDAOTest.h"
#include "Account.h"
#include "AccountDAO.h"
#include "INIConfig.h"
#include "DateTime.h"

using namespace WeAP::System;

AccountDAOTest::AccountDAOTest()
{
    this->manager = AccountManagerS::GetInstance();
}

AccountDAOTest::~AccountDAOTest()
{
}

void AccountDAOTest::TestInsert()
{
    Account account;
    account.accountId = this->manager->keyGenerator.NewAccountId();
    account.balance = 1;
    account.status = Account::Normal;
    account.createTime = DateTime().ToDateTimeString();
    account.modifyTime = DateTime().ToDateTimeString();

    this->manager->accountDAO.Insert(account);

    Account accountDB;
    this->manager->accountDAO.Query(account.accountId, account.currencyType, accountDB);

    EXPECT_TRUE(account.Equals(accountDB));

}

void AccountDAOTest::TestUpdate()
{
    Account account;  //插入前内存account
    account.accountId = this->manager->keyGenerator.NewAccountId();
    account.balance = 1;
    account.status = Account::Normal;
    account.createTime = DateTime().ToDateTimeString();
    account.modifyTime = DateTime().ToDateTimeString();

    this->manager->accountDAO.Insert(account);

    Account accountDB;  //插入后DB account
    this->manager->accountDAO.Query(account.accountId, account.currencyType, accountDB);
    accountDB.balance += 1;

    this->manager->accountDAO.Update(accountDB);

    Account accountDB2; //DB被修改后的account
    this->manager->accountDAO.Query(account.accountId, account.currencyType, accountDB2);

    EXPECT_FALSE(account.Equals(accountDB2));

    EXPECT_TRUE(accountDB.Equals(accountDB2));

}


TEST_F(AccountDAOTest, TestInsert)
{
    TestInsert();
}


TEST_F(AccountDAOTest, TestUpdate)
{
    TestUpdate();
}

