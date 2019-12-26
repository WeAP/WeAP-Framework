#ifndef __ObjectTest_H__
#define __ObjectTest_H__

#include "gtest/gtest.h"
#include <stdint.h>

//EXPECT_EQ(expectedResult, result);    �ж����
//EXPECT_NE(expectedResult, result);    �жϲ����
//EXPECT_LT(val1, val2);                      �ж�С��
//EXPECT_GT(val1, val2);                      �жϴ���

//EXPECT_TRUE(condition);            
//EXPECT_FALSE(condition);    

//ASSERT_THROW(Convert::ToInt(str4), Exception);
//ASSERT_THROW(statement, exception_type);  
//ASSERT_ANY_THROW(statement);  
//ASSERT_NO_THROW(statement);

class ObjectTest : public testing::Test
{
public:
    ObjectTest()
    {
        this->accountId1 = 100001;
        this->accountId2 = 100002;
        this->currencyType = 1;
    };
    virtual ~ObjectTest(){};

    virtual void SetUp() 
    {

    };
    virtual void TearDown() 
    {
    };

    uint64_t accountId1;
    uint64_t accountId2;
    uint32_t currencyType;

};


#endif

