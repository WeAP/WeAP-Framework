#include "AccountantTest.h"
#include "Account.h"
#include "AccountDAO.h"
#include "INIConfig.h"
#include "DateTime.h"
#include "Accountant.h"

using namespace WeAP::System;

AccountantTest::AccountantTest()
{
    this->manager = AccountManagerS::GetInstance();
}

AccountantTest::~AccountantTest()
{

}

void AccountantTest::TestOpenAccount()
{
    Account account;  //插入前内存account
    account.accountId = this->manager->keyGenerator.NewAccountId();
    account.accountType = Account::UserAccount;

    Accountant accountant;
    accountant.OpenAccount(account);

    Account accountDB;
    accountant.GetAccount(account.accountId, accountDB);

    EXPECT_TRUE(account.Equals(accountDB));

}


TEST_F(AccountantTest, TestOpenAccount)
{
    TestOpenAccount();
}
