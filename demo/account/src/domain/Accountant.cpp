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
    AccountRecord accountRecord;


    try
    {
        //this->manger->accountDAO.Begin();

        this->manger->accountDAO.Insert(account);
        //this->manger->accountRecordDAO.Insert(accountRecord);

        //this->manger->accountDAO.Commit();
    }
    catch(const Exception& ex)
    {
        //this->manger->accountDAO.Rollback();
    }
    catch(const std::exception& e)
    {
        //this->manger->accountDAO.Rollback();
    }
    catch(...)
    {
        //this->manger->accountDAO.Rollback();
    }


    
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

void TransferIn(Account& outerAccount, Account& innerAccount)
{

}
void TransferOut(Account& innerAccount, Account& outerAccount)
{

}

void Accountant::Transfer(Account& fromAccount, Account& toAccount)
{
    
}