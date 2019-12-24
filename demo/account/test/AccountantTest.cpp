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

void AccountantTest::TestTransfer()
{
    Account fromAccount;
    fromAccount.accountId = this->manager->keyGenerator.NewAccountId();

    Account toAccount;
    toAccount.accountId = this->manager->keyGenerator.NewAccountId();

    int64_t amount = 10;

    Accountant accountant;
    //accountant.Transfer(fromAccount, toAccount, amount);


    Account fromAccountDB;
    Account toAccountDB;
    //accountant.GetAccount(fromAccount.accountId, fromAccountDB);
    //accountant.GetAccount(toAccount.accountId, toAccountDB);

    //EXPECT_TRUE(fromAccount.Equals(fromAccountDB));
    //EXPECT_TRUE(toAccount.Equals(toAccountDB));

}


TEST_F(AccountantTest, TestOpenAccount)
{
    TestOpenAccount();
}

TEST_F(AccountantTest, TestTransfer)
{
    TestTransfer();
}


