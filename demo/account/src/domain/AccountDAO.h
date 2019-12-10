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

    void Insert(Account& account);

    void Query(uint64_t accountId, Account& account);

protected:

};



#endif 
