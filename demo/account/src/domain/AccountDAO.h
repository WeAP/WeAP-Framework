#ifndef __WeAP_AccountDAO_H__
#define __WeAP_AccountDAO_H__

#include "MySQLDAO.h"
#include "Account.h"

using namespace WeAP::MySQL;

class AccountDAO : public MySQLDAO
{
public:
    AccountDAO();
    virtual ~AccountDAO();

    void Insert(Account& account, MySQLTransaction& trans);
    void Update(Account& account, MySQLTransaction& trans);
    
    void Insert(Account& account, MySQL* transHandler = NULL);
    void Update(Account& account, MySQL* transHandler = NULL);


    void Query(uint64_t accountId, uint32_t currencyType, Account& account, MySQLTransaction& trans);
    void Query(uint64_t accountId, uint32_t currencyType, Account& account, MySQL* transHandler = NULL);
    void Query(uint64_t accountId, uint32_t currencyType, KVMap& record,MySQL* transHandler = NULL);



};



#endif 
