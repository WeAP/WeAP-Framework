#ifndef __WeAP_CharsetTest_H__
#define __WeAP_CharsetTest_H__

#include "ObjectTest.h"


class CharsetTest : public ObjectTest
{
public:
    CharsetTest();
    virtual ~CharsetTest();

    void TestIsUTF8();

    void IsPhoneNum();

    void IsBankAccount();

protected:


};



#endif //__WEAP_DATETIMETEST_H__
