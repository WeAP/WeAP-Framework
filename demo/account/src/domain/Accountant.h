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

    void Transfer(Account& fromAccount, Account& toAccount, int64_t amount);

    void GetAccount(uint64_t accountId, Account& account);

    void GetAccountTransaction(uint64_t accountTransactionId, AccountTransaction& accountTransaction);


    void StartTransaction(Account& fromAccount, Account& toAccount, int64_t amount, uint64_t& accountTransactionId);
    void FinishTransaction(uint64_t accountTransactionId);
    void MinusMoney(Account& account, int64_t amount, uint64_t accountTransactionId);
    void PlusMoney(Account& account, int64_t amount);

protected:
    AccountManager* manger;
};



#endif 
