#ifndef __ObjectTest_H__
#define __ObjectTest_H__

#include "gtest/gtest.h"

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
    virtual void SetUp() 
    {

    };
    virtual void TearDown() 
    {
    };
};


#endif

