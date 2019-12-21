#ifndef __WeAP_Account_H__
#define __WeAP_Account_H__

#include "Entity.h"

using namespace WeAP::Framework;


class Account : public Entity
{
public:
    enum AccountType
    {
        UserAccount = 1, 
        MerchantAccount = 2,
        BankAccount = 3
    };

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
    Account();
    virtual ~Account();

    Account& operator=(const KVMap &record);
    bool Equals(const Account& other);

    virtual string GenDataSign() const;

public:
    uint64_t accountId;
    uint32_t accountType;
    uint32_t currencyType;
    int64_t balance;
    int64_t freezedBalance;
    uint32_t status;
    string remark;

    uint64_t dataVersion;
    string dataSign;
    string createTime;
    string modifyTime;

protected:

};



#endif 
