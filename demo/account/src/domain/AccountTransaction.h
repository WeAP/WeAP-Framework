#ifndef __WeAP_AccountTransaction_H__
#define __WeAP_AccountTransaction_H__

#include "Entity.h"
#include "Account.h"

using namespace WeAP::Framework;

class AccountTransaction : public Entity
{
public:
    enum Status
    {
        Normal = 1,
        Frozen = 2,
        Closed = 9
    };


public:
    AccountTransaction();
    virtual ~AccountTransaction();

public:
    uint64_t accountId;

    Account::CurrencyType currencyType;
    int64_t balance;
    int64_t freezedAmount;
    Status status;

    uint64_t dataVersion;
    string dataSign;
    string createTime;
    string modifyTime;

protected:

};



#endif 
