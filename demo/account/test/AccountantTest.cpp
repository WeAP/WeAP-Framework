#include "AccountantTest.h"
#include "Account.h"
#include "AccountDAO.h"
#include "INIConfig.h"
#include "DateTime.h"
#include "Accountant.h"

using namespace WeAP::System;

AccountantTest::AccountantTest()
{
}

AccountantTest::~AccountantTest()
{

}

void AccountantTest::TestOpenAccount()
{
    Account account;  //插入前内存account
    account.accountId = time(NULL) + 5;
    account.balance = 1;
    account.status = Account::Normal;
    account.createTime = DateTime().ToDateTimeString();
    account.modifyTime = DateTime().ToDateTimeString();

    Accountant accountant;
    accountant.OpenAccount(account);


}


TEST_F(AccountantTest, TestOpenAccount)
{
    TestOpenAccount();
}
