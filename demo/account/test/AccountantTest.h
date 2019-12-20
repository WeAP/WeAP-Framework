#ifndef __WeAP_AccountantTest_H__
#define __WeAP_AccountantTest_H__

#include "ObjectTest.h"
#include "AccountManager.h"

class AccountantTest: public ObjectTest
{
public:
    AccountantTest();
    virtual ~AccountantTest();

    void TestOpenAccount();
    void TestTransfer();

protected:
    AccountManager* manager;

};



#endif 
