#include "AccountPlusHandler.h"


AccountPlusHandler::AccountPlusHandler()
{

}

AccountPlusHandler::~AccountPlusHandler()
{

}

void AccountPlusHandler::Prepare()
{

}

void AccountPlusHandler::Commit()
{
    uint64_t accountId = this->stContext->params.GetInt64("accountId");
    uint32_t currencyType = this->stContext->params.GetInt32("currencyType");
    int64_t amount = this->stContext->params.GetInt64("amount");
    string txnNO = this->stContext->params.GetString("txnNO");

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

void AccountPlusHandler::Rollback()
{

}

void AccountPlusHandler::Finish()
{
    
}