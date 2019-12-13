#ifndef __WeAP_AccountRecordDAO_H__
#define __WeAP_AccountRecordDAO_H__

#include "MySQLDAO.h"
#include "Account.h"

using namespace WeAP::MySQL;

class AccountRecordDAO : public MySQLDAO
{
public:
    AccountRecordDAO();
    virtual ~AccountRecordDAO();

    void Insert(Account& account);

    void Query(uint64_t accountId, Account& account);

protected:

};



#endif 
