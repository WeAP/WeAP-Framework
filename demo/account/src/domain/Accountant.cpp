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
                        int64_t amount,
                        const string& txnNO)
{
    this->MinusMoney(fromAccountId, currencyType, amount, txnNO);

    this->CreateAccountTransaction(fromAccountId, toAccountId, currencyType, amount, txnNO);

    this->PlusMoney(toAccountId, currencyType, amount, txnNO);
}

void Accountant::CreateAccountTransaction(uint64_t fromAccountId, 
                                        uint64_t toAccountId,
                                        uint32_t currencyType,
                                        int64_t amount,
                                        const string& txnNO)
{
    AccountTransaction trans;
    //trans.accountTransactionId = 
    trans.txnNO = txnNO;
    trans.type = AccountTransaction::User2User;
    trans.status = AccountTransaction::Started;
    
    trans.accountId = fromAccountId;
    trans.currencyType = currencyType;
    trans.vsAccountId = toAccountId;
    trans.vsCurrencyType = currencyType;
    trans.amount = amount;
    trans.freezedAmount = 0;
    //trans.remark = ;

    this->manger->accountTransactionDAO.Insert(trans);

}


void Accountant::MinusMoney(uint64_t accountId, uint32_t currencyType, int64_t amount, const string& txnNO)
{
    MySQLTransaction trans = this->manger->accountDAO.GetTransaction();
    trans.Begin();
    Account account;
    this->manger->accountDAO.Query(accountId, currencyType, account, trans);

    account.balance = account.balance - amount;
    account.txnNO = txnNO;

    AccountRecord accountRecord;
    accountRecord.SetAccount(account);
    //accountRecord.accountTransactionId = accountTransactionId;
    accountRecord.opType = AccountRecord::OP_TransferOut;
    accountRecord.opAmount = amount;
    accountRecord.opFreezedAmount = 0;
    //accountRecord.accountEvidenceId
    accountRecord.txnNO = txnNO;

    this->manger->accountDAO.Update(account, trans);
    this->manger->accountRecordDAO.Insert(accountRecord, trans);
    trans.Commit();
}

void Accountant::PlusMoney(uint64_t accountId, uint32_t currencyType, int64_t amount, const string& txnNO)
{
    MySQLTransaction trans = this->manger->accountDAO.GetTransaction();
    trans.Begin();

    Account account;
    this->manger->accountDAO.Query(accountId, currencyType, account, trans);

    account.balance = account.balance + amount;
    account.txnNO = txnNO;

    AccountRecord accountRecord;
    accountRecord.SetAccount(account);
    //accountRecord.accountTransactionId = accountTransactionId;
    accountRecord.opType = AccountRecord::OP_TransferIn;
    accountRecord.opAmount = amount;
    accountRecord.opFreezedAmount = 0;
    accountRecord.txnNO = txnNO;

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