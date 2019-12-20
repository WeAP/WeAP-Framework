#include "AccountTransaction.h"

using namespace WeAP::System;

AccountTransaction::AccountTransaction()
{
}

AccountTransaction::~AccountTransaction()
{

}


AccountTransaction& AccountTransaction::operator=(const KVMap &record)
{
    COPY_FIELD(accountId, UInt64);
    COPY_FIELD(currencyType, UInt32);
    COPY_FIELD(status, UInt32);
    COPY_FIELD(dataVersion, UInt64);
    COPY_FIELD(dataSign, String);
    COPY_FIELD(createTime, String);
    COPY_FIELD(modifyTime, String);
    return *this;
}

bool AccountTransaction::Equals(const AccountTransaction& other)
{
    EQUAL_FIELD(accountId);
    EQUAL_FIELD(currencyType);
    EQUAL_FIELD(status);
    EQUAL_FIELD(dataVersion);
    EQUAL_FIELD(dataSign);
    EQUAL_FIELD(createTime);
    EQUAL_FIELD(modifyTime);

    return true;
}

string AccountTransaction::GenDataSign() const
{
    stringstream src;
    //src << this->accountId;
    src << this->currencyType;
    src << this->status;
    //src << this->modifyTime;
    return src.str();
}
