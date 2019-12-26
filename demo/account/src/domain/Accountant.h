#ifndef __WeAP_Accountant_H__
#define __WeAP_Accountant_H__

#include "Handler.h"
#include "Account.h"
#include "AccountManager.h"

using namespace WeAP::Framework;

class Accountant : public Handler
{

public:
    Accountant();
    virtual ~Accountant();

    void OpenAccount(Account& account);
    void CloseAccount(Account& account);

    void FreezeAccount(Account& account);
    void UnfreezeAccount(Account& account);

    void TransferIn(Account& bankAccount, Account& innerAccount);  ///< 充值
    void TransferOut(Account& innerAccount, Account& bankAccount); ///< 提现

    void Pay(Account& userAccount, Account& mchAccount);  ///< 支付

    void Drawback(Account& mchAccount, Account& userAccount);  ///< 退款

    void GetAccount(uint64_t accountId, uint32_t currencyType, Account& account);

    void GetAccountTransaction(uint64_t accountTransactionId, AccountTransaction& accountTransaction);

    void Transfer(uint64_t fromAccountId, 
                  uint64_t toAccountId,
                  uint32_t currencyType,
                  int64_t amount);

    void MinusMoney(uint64_t accountId, uint32_t currencyType, int64_t amount, uint64_t accountTransactionId);
    void PlusMoney(uint64_t accountId, uint32_t currencyType, int64_t amount, uint64_t accountTransactionId);


protected:
    AccountManager* manger;

    uint64_t accountId1;
    uint64_t accountId2;
};



#endif 
