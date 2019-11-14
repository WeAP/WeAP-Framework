#include "DateTimeTest.h"
#include "DateTime.h"

using namespace WeAP::System;

DateTimeTest::DateTimeTest()
{
}

DateTimeTest::~DateTimeTest()
{

}

void DateTimeTest::TestNormal()
{
    EXPECT_EQ("2019-11-13 18:34:13", DateTime("2019-11-13 18:34:13").ToDateTimeString());

}


TEST_F(DateTimeTest, TestNormal)
{
    TestNormal();
}
