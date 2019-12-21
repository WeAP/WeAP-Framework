#include "AccountRecord.h"

using namespace WeAP::System;

AccountRecord::AccountRecord()
{
}

AccountRecord::~AccountRecord()
{

}


void AccountRecord::SetAccount(const Account& account)
{
    this->accountId = account.accountId;
    this->accountType = account.accountType;
    this->currencyType = account.currencyType;
    this->balance = account.balance;
    this->freezedBalance = account.freezedBalance;
    this->status = account.status;
    this->remark = account.remark;
}