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
    account.freezedBalance = 0;
    account.status = Account::Normal;
    //string remark;

    AccountRecord accountRecord;
    accountRecord.SetAccount(account);
    accountRecord.opType = AccountRecord::OP_OpenAccount;
    accountRecord.opAmount = 0;
    accountRecord.opFreezedAmount = 0;


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

void Accountant::Transfer(uint64_t fromAccountId, 
                  uint64_t toAccountId,
                  uint32_t currencyType,
                  int64_t amount)
{
    uint64_t accountTransactionId = this->manger->keyGenerator.NewAccountTransactionId();

    this->MinusMoney(fromAccountId, currencyType, amount, accountTransactionId);

    this->PlusMoney(toAccountId, currencyType, amount, accountTransactionId);
}

void Accountant::MinusMoney(uint64_t accountId, uint32_t currencyType, int64_t amount, uint64_t accountTransactionId)
{
    MySQLTransaction trans = this->manger->accountDAO.GetTransaction();
    trans.Begin();
    Account account;
    this->manger->accountDAO.Query(accountId, currencyType, account, trans);

    account.balance = account.balance - amount;

    AccountRecord accountRecord;
    accountRecord.SetAccount(account);
    accountRecord.accountTransactionId = accountTransactionId;
    accountRecord.opType = AccountRecord::OP_TransferOut;
    accountRecord.opAmount = amount;
    accountRecord.opFreezedAmount = 0;
    //accountRecord.accountEvidenceId

    this->manger->accountDAO.Update(account, trans);
    this->manger->accountRecordDAO.Insert(accountRecord, trans);
    trans.Commit();
}

void Accountant::PlusMoney(uint64_t accountId, uint32_t currencyType, int64_t amount, uint64_t accountTransactionId)
{
    MySQLTransaction trans = this->manger->accountDAO.GetTransaction();
    trans.Begin();

    Account account;
    this->manger->accountDAO.Query(accountId, currencyType, account, trans);

    account.balance = account.balance + amount;
    AccountRecord accountRecord;
    accountRecord.SetAccount(account);
    //accountRecord.accountTransactionId = accountTransactionId;
    accountRecord.opType = AccountRecord::OP_TransferIn;
    accountRecord.opAmount = amount;
    accountRecord.opFreezedAmount = 0;


    this->manger->accountDAO.Update(account, trans);
    this->manger->accountRecordDAO.Insert(accountRecord, trans);
    trans.Commit();
}


void Accountant::GetAccount(uint64_t accountId, uint32_t currencyType, Account& account)
{
    this->manger->accountDAO.Query(accountId, currencyType, account);
}

void Accountant::GetAccountTransaction(uint64_t accountTransactionId, AccountTransaction& accountTransaction)
{
    this->manger->accountTransactionDAO.Query(accountTransactionId, accountTransaction);
}