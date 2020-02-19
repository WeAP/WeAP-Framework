#include "CharsetTest.h"
#include "Charset.h"
#include "StringUtil.h"

using namespace WeAP::System;



bool IsPhoneNum(const string& str)
{
    if (str.empty())
    {
        return true;
    }

    for (size_t i = 0; i < str.size(); i++)
    {
        if (!(isdigit(str[i]) || str[i] == '-'))
        {
            return false;
        }
    }

    return true;
}


bool IsBankAccount(const string& str)
{
    if (str.empty())
    {
        return true;
    }

    for (size_t i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}



CharsetTest::CharsetTest()
{
}

CharsetTest::~CharsetTest()
{

}

void CharsetTest::TestIsUTF8()
{
    string adress;

    adress = "湖北省武汉市武汉大道1号";
    EXPECT_EQ(true, Charset::IsUTF8(adress, true, true));

    adress = "武汉新技术开发区A栋7、8、9层";
    EXPECT_EQ(true, Charset::IsUTF8(adress, true, true));

    adress = "北京村南100米办公楼106、室";
    EXPECT_EQ(true, Charset::IsUTF8(adress, true, true));

    string str;
    str = "中国建设银行股份有限公司武汉光谷自贸区分行";
    EXPECT_EQ(true, Charset::IsUTF8(str, true, false));


    str = "北京 ";
    EXPECT_EQ(false, Charset::IsUTF8(str, true, true));

    str = "北京\n";
    EXPECT_EQ(false, Charset::IsUTF8(str, true, true));

    str = "科技有限公司";
    EXPECT_EQ(true, Charset::IsUTF8(str, true, true));


}

void CharsetTest::IsPhoneNum()
{
    string str;

    str = "13698328648";
    EXPECT_EQ(true, ::IsPhoneNum(str));

    str = "0532-8606810";
    EXPECT_EQ(true, ::IsPhoneNum(str));

    str = "0123456789;";
    EXPECT_EQ(false, ::IsPhoneNum(str));

    str = "0123456789 ";
    EXPECT_EQ(false, ::IsPhoneNum(str));

}

void CharsetTest::IsBankAccount()
{
    string bankAccount;

    bankAccount = "137141512010000255";
    EXPECT_EQ(true, ::IsBankAccount(bankAccount));

    bankAccount = "1371 4151 2010 0002 55";
    EXPECT_EQ(false, ::IsBankAccount(bankAccount));

    bankAccount = "13714151010000255A";
    EXPECT_EQ(false, ::IsBankAccount(bankAccount));
}


TEST_F(CharsetTest, TestIsUTF8)
{
    TestIsUTF8();
}

TEST_F(CharsetTest, IsPhoneNum)
{
    IsPhoneNum();
}

TEST_F(CharsetTest, IsBankAccount)
{
    IsBankAccount();
}
