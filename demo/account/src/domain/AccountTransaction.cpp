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
    COPY_FIELD(accountTransactionId, UInt64);
    COPY_FIELD(type, UInt32);
    COPY_FIELD(status, UInt32);
    COPY_FIELD(accountId, UInt64);
    COPY_FIELD(accountType, UInt32);
    COPY_FIELD(currencyType, UInt32);
    COPY_FIELD(amount, Int64);
    COPY_FIELD(freezedAmount, Int64);
    COPY_FIELD(remark, String);
    COPY_FIELD(dataVersion, UInt64);
    COPY_FIELD(dataSign, String);
    COPY_FIELD(createTime, String);
    COPY_FIELD(modifyTime, String);
    return *this;
}

bool AccountTransaction::Equals(const AccountTransaction& other)
{
    EQUAL_FIELD(accountTransactionId);
    EQUAL_FIELD(type);
    EQUAL_FIELD(status);
    EQUAL_FIELD(accountId);
    EQUAL_FIELD(accountType);
    EQUAL_FIELD(currencyType);
    EQUAL_FIELD(amount);
    EQUAL_FIELD(freezedAmount);
    EQUAL_FIELD(remark);
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
    src << this->amount;
    //src << this->modifyTime;
    return src.str();
}
