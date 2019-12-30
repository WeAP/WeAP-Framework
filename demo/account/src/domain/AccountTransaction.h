#ifndef __WeAP_AccountTransaction_H__
#define __WeAP_AccountTransaction_H__

#include "Entity.h"
#include "Account.h"
#include "ObjectList.h"

using namespace WeAP::Framework;

class AccountTransaction : public Entity
{
public:
    enum Status
    {
        Started  = 1,
        Finished = 2,
        Suspend  = 3,
        Freezed  = 4,
        Cancel   = 5
    };

    enum Type
    {
        User2User = 1,
        User2Merchant = 2,
        User2Bank = 3
    };

public:
    AccountTransaction();
    virtual ~AccountTransaction();

    AccountTransaction& operator=(const KVMap &record);
    bool Equals(const AccountTransaction& other);

    virtual string GenDataSign() const;

public:
    uint64_t accountTransactionId;
    string txnNO;
    uint32_t type;
    uint32_t status;
    uint64_t accountId;
    uint32_t accountType;

    uint64_t vsAccountId;
    uint32_t vsCurrencyType;

    uint32_t currencyType;
    int64_t amount;
    int64_t freezedAmount;
    string remark;

    string dtNO;
    string tNO;
    string sNO;

    uint64_t dataVersion;
    string dataSign;
    string createTime;
    string modifyTime;

protected:

};

typedef ObjectList<AccountTransaction> AccountTransactionList;

#endif 
