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

    MySQL* transHandler = this->manger->accountDAO.GetTransHandler();

    try
    {


        transHandler->Begin();

        this->manger->accountDAO.Insert(account, transHandler);
        //this->manger->accountRecordDAO.Insert(accountRecord);

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