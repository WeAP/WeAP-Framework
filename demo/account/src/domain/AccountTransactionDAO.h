#ifndef __WeAP_AccountTransactionDAO_H__
#define __WeAP_AccountTransactionDAO_H__

#include "MySQLDAO.h"
#include "AccountTransaction.h"

using namespace WeAP::MySQL;

class AccountTransactionDAO : public MySQLDAO
{
public:
    AccountTransactionDAO();
    virtual ~AccountTransactionDAO();

    void Insert(AccountTransaction& tx);

    void Query(uint64_t accountId, AccountTransaction& txn);

protected:

};



#endif 
