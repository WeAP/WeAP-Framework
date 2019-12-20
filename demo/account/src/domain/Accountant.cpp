#include "Accountant.h"
#include "AccountRecord.h"

using namespace WeAP::System;

Accountant::Accountant()
{
    this->manger = AccountManagerS::GetInstance();
}

Accountant::~Accountant()
{

}


void Accountant::OpenAccount(Account& account)
{
    account.accountType = Account::UserAccount;
    account.currencyType = Account::CNY;
    account.balance = 0;
    account.freezedAmount = 0;
    account.status = Account::Normal;
    //string remark;

    AccountRecord accountRecord;

    MySQLTransaction trans = this->manger->accountDAO.GetTransaction();

    trans.Begin();

    this->manger->accountDAO.Insert(account, trans);
    this->manger->accountRecordDAO.Insert(accountRecord, trans);

    trans.Commit();
}

void Accountant::CloseAccount(Account& account)
{

}

void Accountant::FreezeAccount(Account& account)
{

}

void Accountant::UnfreezeAccount(Account& account)
{

}

void Accountant::TransferIn(Account& outerAccount, Account& innerAccount)
{

}
void Accountant::TransferOut(Account& innerAccount, Account& outerAccount)
{

}

void Accountant::Transfer(Account& fromAccount, Account& toAccount)
{
    AccountTransaction accountTransaction;
    this->manger->accountTransactionDAO.Insert(accountTransaction);
}


void Accountant::GetAccount(uint64_t accountId, Account& account)
{
    this->manger->accountDAO.Query(accountId, account);
}

void Accountant::GetAccountTransaction(uint64_t accountTransactionId, AccountTransaction& accountTransaction)
{
    this->manger->accountTransactionDAO.Query(accountTransactionId, accountTransaction);
}