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
                        const string& txnNo)
{
    this->SaveAccountTransaction(fromAccountId, toAccountId, currencyType, amount, txnNo);

    this->MinusMoney(fromAccountId, currencyType, amount, txnNo);

    this->PlusMoney(toAccountId, currencyType, amount, txnNo);
}

void Accountant::SaveAccountTransaction(uint64_t fromAccountId, 
                                        uint64_t toAccountId,
                                        uint32_t currencyType,
                                        int64_t amount,
                                        const string& txnNo)
{
    AccountTransaction trans;
    //trans.accountTransactionId = 
    trans.txnNO = txnNo;
    trans.type = AccountTransaction::User2User;
    trans.status = AccountTransaction::Started;
    
    trans.accountId = fromAccountId;
    trans.currencyType = currencyType;
    trans.vsAccountId = toAccountId;
    trans.vsSurrencyType = currencyType;
    trans.amount = amount;
    trans.freezedAmount = 0;
    //trans.remark = ;

    this->manger->accountTransactionDAO.Insert(accountTransacion);

}


void Accountant::MinusMoney(uint64_t accountId, uint32_t currencyType, int64_t amount, const string& txnNo)
{
    MySQLTransaction trans = this->manger->accountDAO.GetTransaction();
    trans.Begin();
    Account account;
    this->manger->accountDAO.Query(accountId, currencyType, account, trans);

    account.balance = account.balance - amount;
    account.txnNo = txnNo;

    AccountRecord accountRecord;
    accountRecord.SetAccount(account);
    accountRecord.accountTransactionId = accountTransactionId;
    accountRecord.opType = AccountRecord::OP_TransferOut;
    accountRecord.opAmount = amount;
    accountRecord.opFreezedAmount = 0;
    //accountRecord.accountEvidenceId
    accountRecord.txnNo = txnNo;

    this->manger->accountDAO.Update(account, trans);
    this->manger->accountRecordDAO.Insert(accountRecord, trans);
    trans.Commit();
}

void Accountant::PlusMoney(uint64_t accountId, uint32_t currencyType, int64_t amount, const string& txnNo)
{
    MySQLTransaction trans = this->manger->accountDAO.GetTransaction();
    trans.Begin();

    Account account;
    this->manger->accountDAO.Query(accountId, currencyType, account, trans);

    account.balance = account.balance + amount;
    account.txnNo = txnNo;

    AccountRecord accountRecord;
    accountRecord.SetAccount(account);
    //accountRecord.accountTransactionId = accountTransactionId;
    accountRecord.opType = AccountRecord::OP_TransferIn;
    accountRecord.opAmount = amount;
    accountRecord.opFreezedAmount = 0;
    accountRecord.txnNo = txnNo;

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