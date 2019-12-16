#ifndef __WeAP_AccountDAOTest_H__
#define __WeAP_AccountDAOTest_H__

#include "MySQLDAOTest.h"
#include "AccountManager.h"

class AccountDAOTest: public MySQLDAOTest
{
public:
    AccountDAOTest();
    virtual ~AccountDAOTest();

    void TestInsert();

    void TestUpdate();

protected:
    AccountManager* manager;

};



#endif 
