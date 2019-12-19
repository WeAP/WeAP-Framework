#ifndef __WeAP_AccountRecordDAO_H__
#define __WeAP_AccountRecordDAO_H__

#include "MySQLDAO.h"
#include "AccountRecord.h"

using namespace WeAP::MySQL;

class AccountRecordDAO : public MySQLDAO
{
public:
    AccountRecordDAO();
    virtual ~AccountRecordDAO();

    void Insert(AccountRecord& accountRecord, MySQLTransaction& trans);
    void Insert(AccountRecord& accountRecord, MySQL* transHandler = NULL);

    void Query(uint64_t accountId, AccountRecordList& list);

protected:

};



#endif 
