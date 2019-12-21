#ifndef __WeAP_AccountRecord_H__
#define __WeAP_AccountRecord_H__

#include "Entity.h"
#include "ObjectList.h"

using namespace WeAP::Framework;

class AccountRecord : public Entity
{
public:
    enum OPType
    {
        OP_OpenAccount = 1,
        OP_TransferIn = 2,
        OP_TransferOut = 3,
        OP_FreezeAccount = 4,
        OP_UnfreezeAccount = 5,

        OP_CloseAccount = 9,
    };
public:
    AccountRecord();
    virtual ~AccountRecord();

    void SetAccount(const Account& account);

public:
    uint64_t accountId;
    uint32_t accountType;
    uint32_t currencyType;
    int64_t balance;
    int64_t freezedBalance;
    uint32_t status;
    string remark;

    uint64_t accountTransactionId;

    int opType;
    int64_t opAmount;
    int64_t opFreezedAmount;
    //int64_t opBalance;
    //int64_t opFreezedBalance;

    string accountEvidenceId;

    uint64_t dataVersion;
    string dataSign;
    string createTime;
    string modifyTime;

protected:

};


typedef ObjectList<AccountRecord> AccountRecordList;

#endif 
