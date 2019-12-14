#include "Account.h"

using namespace WeAP::System;

Account::Account()
{
    this->accountId = 0;
    this->accountType = UserAccount;
    this->currencyType = CNY;
    this->balance = 0;
    this->freezedAmount = 0;
    this->status = Normal;
    this->dataVersion = 0;
    //this->dataSign;
    //this->createTime;
    //this->modifyTime;
}

Account::~Account()
{
}

Account& Account::operator=(const KVMap &record)
{
    COPY_FIELD(accountId, UInt64);
    COPY_FIELD(accountType, UInt32);
    COPY_FIELD(currencyType, UInt32);
    COPY_FIELD(balance, Int64);
    COPY_FIELD(freezedAmount, UInt64);
    COPY_FIELD(status, UInt32);
    COPY_FIELD(dataVersion, UInt64);
    COPY_FIELD(createTime, String);
    COPY_FIELD(modifyTime, String);
    return *this;
}

bool Account::Equals(const Account& other)
{
    EQUAL_FIELD(accountId);
    EQUAL_FIELD(currencyType);
    EQUAL_FIELD(balance);
    EQUAL_FIELD(freezedAmount);
    EQUAL_FIELD(status);
    EQUAL_FIELD(dataVersion);
    EQUAL_FIELD(dataSign);
    EQUAL_FIELD(createTime);
    EQUAL_FIELD(modifyTime);

    return true;
}

