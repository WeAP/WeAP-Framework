#include "AccountRecord.h"

using namespace WeAP::System;

AccountRecord::AccountRecord()
{
}

AccountRecord::~AccountRecord()
{

}

AccountRecord& AccountRecord::operator=(const KVMap &record)
{
    COPY_FIELD(accountRecordId, UInt64);
    COPY_FIELD(accountId, UInt64);
    COPY_FIELD(accountType, UInt32);
    COPY_FIELD(currencyType, UInt32);
    COPY_FIELD(balance, Int64 );
    COPY_FIELD(freezedBalance, Int64 );
    COPY_FIELD(status, UInt32);
    COPY_FIELD(remark, String);
    COPY_FIELD(opType, Int32 );
    COPY_FIELD(opAmount, Int64 );
    COPY_FIELD(opFreezedAmount, Int64 );
    COPY_FIELD(accountTransactionId, UInt64);
    COPY_FIELD(accountEvidenceId, String);
    COPY_FIELD(dataVersion, UInt64);
    COPY_FIELD(dataSign, String);
    COPY_FIELD(createTime, String);
    COPY_FIELD(modifyTime, String);

    return *this;
}
bool AccountRecord::Equals(const AccountRecord& other)
{
	EQUAL_FIELD(accountId);
	EQUAL_FIELD(accountRecordId);
    EQUAL_FIELD(accountId);
    EQUAL_FIELD(accountType);
    EQUAL_FIELD(currencyType);
    EQUAL_FIELD(balance);
    EQUAL_FIELD(freezedBalance);
    EQUAL_FIELD(status);
    EQUAL_FIELD(remark);
    EQUAL_FIELD(opType);
    EQUAL_FIELD(opAmount);
    EQUAL_FIELD(opFreezedAmount);
    EQUAL_FIELD(accountTransactionId);
    EQUAL_FIELD(accountEvidenceId);
    EQUAL_FIELD(dataVersion);
    EQUAL_FIELD(dataSign);
    EQUAL_FIELD(createTime);
    EQUAL_FIELD(modifyTime);

    return true;
}

string AccountRecord::GenDataSign() const
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



    uint64_t accountRecordId;
    uint64_t accountId;
    uint32_t accountType;
    uint32_t currencyType;
    int64_t balance;
    int64_t freezedBalance;
    uint32_t status;
    string remark;
    int opType;
    int64_t opAmount;
    int64_t opFreezedAmount;
    uint64_t accountTransactionId;
    string accountEvidenceId;
    uint64_t dataVersion;
    string dataSign;
    string createTime;
    string modifyTime;
