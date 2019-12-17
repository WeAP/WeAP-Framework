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
/*
    MySQL* transHandler = this->manger->accountDAO.GetTransHandler();

    try
    {
        transHandler->Begin();

        this->manger->accountDAO.Insert(account, transHandler);
        this->manger->accountRecordDAO.Insert(accountRecord, transHandler);

        transHandler->Commit();
    }
    catch(const Exception& ex)
    {
        transHandler->Rollback();
    }
    catch(const std::exception& e)
    {
        transHandler->Rollback();
    }
    catch(...)
    {
        transHandler->Rollback();
    }
*/

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
    
}