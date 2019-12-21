#include "Account.h"

using namespace WeAP::System;

Account::Account()
{
    this->accountId = 0;
    this->accountType = UserAccount;
    this->currencyType = CNY;
    this->balance = 0;
    this->freezedBalance = 0;
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
    COPY_FIELD(freezedBalance, UInt64);
    COPY_FIELD(status, UInt32);    
    COPY_FIELD(remark, String);
    COPY_FIELD(dataVersion, UInt64);
    COPY_FIELD(dataSign, String);
    COPY_FIELD(createTime, String);
    COPY_FIELD(modifyTime, String);
    return *this;
}

bool Account::Equals(const Account& other)
{
    EQUAL_FIELD(accountId);
    EQUAL_FIELD(accountType);
    EQUAL_FIELD(currencyType);
    EQUAL_FIELD(balance);
    EQUAL_FIELD(freezedBalance);
    EQUAL_FIELD(status);
    EQUAL_FIELD(remark);
    EQUAL_FIELD(dataVersion);
    EQUAL_FIELD(dataSign);
    EQUAL_FIELD(createTime);
    EQUAL_FIELD(modifyTime);

    return true;
}

string Account::GenDataSign() const
{
    stringstream src;
    //src << this->accountId;
    src << this->accountType;
    src << this->currencyType;
    src << this->balance;
    src << this->freezedBalance;
    src << this->status;
    //src << this->modifyTime;
    return src.str();
}