#ifndef __WeAP_AccountDAOTest_H__
#define __WeAP_AccountDAOTest_H__

#include "MySQLDAOTest.h"


class AccountDAOTest: public MySQLDAOTest
{
public:
    AccountDAOTest();
    virtual ~AccountDAOTest();

    void TestInsert();

protected:

};



#endif 
