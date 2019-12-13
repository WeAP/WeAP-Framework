#ifndef __WeAP_AccountRecord_H__
#define __WeAP_AccountRecord_H__

#include "Entity.h"

using namespace WeAP::Framework;

class AccountRecord : public Entity
{
public:
    enum Status
    {
        Normal = 1,
        Frozen = 2,
        Closed = 9
    };
    enum CurrencyType
    {
        CNY = 1
    };

public:
    AccountRecord();
    virtual ~AccountRecord();

public:
    uint64_t accountId;

    CurrencyType currencyType;
    int64_t balance;
    int64_t freezedAmount;
    Status status;

    uint64_t version;
    string sign;
    string createTime;
    string modifyTime;

protected:

};



#endif 
