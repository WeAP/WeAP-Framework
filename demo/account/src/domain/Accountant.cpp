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

void Accountant::Transfer(Account& fromAccount, Account& toAccount, int64_t amount)
{
    uint64_t accountTransactionId;
    this->StartTransaction(fromAccount, toAccount, amount, accountTransactionId);

    this->MinusMoney(fromAccount, amount, accountTransactionId);

    this->PlusMoney(toAccount, amount);

    this->FinishTransaction(accountTransactionId);

}

void Accountant::StartTransaction(Account& fromAccount, Account& toAccount, int64_t amount, uint64_t& accountTransactionId)
{
    AccountTransaction accountTransaction;
    accountTransaction.accountTransactionId = this->manger->keyGenerator.NewAccountTransactionId();
    accountTransaction.type = AccountTransaction::User2User;
    accountTransaction.status = AccountTransaction::Started;

    accountTransaction.accountId = fromAccount.accountId;
    accountTransaction.currencyType = fromAccount.currencyType;
    accountTransaction.amount = amount;

    this->manger->accountTransactionDAO.Insert(accountTransaction);

    accountTransactionId = accountTransaction.accountTransactionId;
    
}

void Accountant::FinishTransaction(uint64_t accountTransactionId)
{
    AccountTransaction accountTransaction;
    this->GetAccountTransaction(accountTransaction);

    accountTransaction.status = AccountTransaction::Finished;

    this->manger->accountTransactionDAO.Update(accountTransaction);
}

void Accountant::MinusMoney(Account& account, int64_t amount, uint64_t accountTransactionId)
{
    account.amount = account.amount - amount;
    AccountRecord accountRecord;
    accountRecord.accountTransactionId = accountTransactionId;
    this->manger->accountDAO.Update(account);
    this->manger->accountRecordDAO.Insert(accountRecord);
}

void Accountant::PlusMoney(Account& account, int64_t amount)
{
    account.amount = account.amount + amount;
    AccountRecord accountRecord;
    this->manger->accountDAO.Update(account);
    this->manger->accountRecordDAO.Insert(accountRecord);
}


void Accountant::GetAccount(uint64_t accountId, Account& account)
{
    this->manger->accountDAO.Query(accountId, account);
}

void Accountant::GetAccountTransaction(uint64_t accountTransactionId, AccountTransaction& accountTransaction)
{
    this->manger->accountTransactionDAO.Query(accountTransactionId, accountTransaction);
}