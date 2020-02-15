#include "RedisDAOTest.h"
#include "DateTime.h"

using namespace WeAP::System;

RedisDAOTest::RedisDAOTest()
{
    //127.0.0.1:6379
    this->redisDAO.Init("127.0.0.1", 6379);
}

RedisDAOTest::~RedisDAOTest()
{

}

void RedisDAOTest::TestGet()
{

}
void RedisDAOTest::TestSet()
{
    string key = "12345";
    string value = "teststr";
    this->redisDAO.Set(key, value);

    string val;
    this->redisDAO.Get(key, val);

    cout << val << endl;

    EXPECT_EQ(value, val);

}


void RedisDAOTest::TestIncr()
{
    string key = "counter";

    int64_t val1 = this->redisDAO.Incr(key);
    //cout << val1 << endl;

    int64_t val2 = this->redisDAO.Incr(key);
    //cout << val2 << endl;

    EXPECT_EQ(val2, val1 + 1);


    val1 = this->redisDAO.IncrBy(key, 5);
    //cout << val1 << endl;

    val2 = this->redisDAO.IncrBy(key, 5);
    //cout << val2 << endl;

    EXPECT_EQ(val2, val1 + 5);


}


TEST_F(RedisDAOTest, TestGet)
{
    TestGet();
}

TEST_F(RedisDAOTest, TestSet)
{
    TestSet();
}

TEST_F(RedisDAOTest, TestIncr)
{
    TestIncr();
}