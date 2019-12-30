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
    accountant.GetAccount(account.accountId, account.currencyType,accountDB);

    EXPECT_TRUE(account.Equals(accountDB));

}

void AccountantTest::TestTransfer()
{
    int64_t amount = 100;
    string txnNo = this->manager->keyGenerator.GenTXNNo();

    Account account1;
    Account account2;

    Accountant accountant;
    accountant.GetAccount(this->accountId1, this->currencyType, account1);
    accountant.GetAccount(this->accountId2, this->currencyType, account2);

    accountant.Transfer(this->accountId1, this->accountId2, this->currencyType, amount, txnNo);

    Account newAccount1;
    Account newAccount2;
    accountant.GetAccount(this->accountId1, this->currencyType, newAccount1);
    accountant.GetAccount(this->accountId2, this->currencyType, newAccount2);

    EXPECT_EQ(newAccount1.balance, account1.balance - 100);
    EXPECT_EQ(newAccount2.balance, account2.balance + 100);

    EXPECT_EQ(account1.balance + account2.balance, newAccount1.balance + newAccount2.balance);


}


TEST_F(AccountantTest, TestOpenAccount)
{
    TestOpenAccount();
}

TEST_F(AccountantTest, TestTransfer)
{
    TestTransfer();
}


