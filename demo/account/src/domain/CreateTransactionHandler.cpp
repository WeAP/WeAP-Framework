#include "CreateTransactionHandler.h"


CreateTransactionHandler::CreateTransactionHandler()
{

}

CreateTransactionHandler::~CreateTransactionHandler()
{

}

void CreateTransactionHandler::Prepare()
{

}

void CreateTransactionHandler::Commit()
{
    uint64_t fromAccountId = this->stContext->params.GetInt64("fromAccountId");
    uint64_t toAccountId = this->stContext->params.GetInt64("toAccountId");
    uint32_t currencyType = this->stContext->params.GetInt32("currencyType");
    int64_t amount = this->stContext->params.GetInt64("amount");
    string txnNO = this->stContext->params.GetString("txnNO");

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

void CreateTransactionHandler::Rollback()
{

}

void CreateTransactionHandler::Finish()
{
    
}