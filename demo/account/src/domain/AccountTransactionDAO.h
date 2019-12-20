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

    void Insert(AccountTransaction& accountTransaction, MySQLTransaction& trans);
    
    void Insert(AccountTransaction& accountTransaction, MySQL* transHandler = NULL);
    void Update(AccountTransaction& accountTransaction, MySQL* transHandler = NULL);

    void Query(uint64_t accountId, AccountTransaction& accountTransaction);
    void Query(uint64_t accountId, KVMap& record);

protected:

};



#endif 
