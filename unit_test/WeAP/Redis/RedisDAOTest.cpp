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
    Redis redis;
    redis.Init("127.0.0.1", 6379);
    redis.Ping();

    string key = "12345";
    string value = "teststr";
    redis.Set(key, value);

    string val;
    redis.Get(key, val);

    cout << val << endl;

    EXPECT_EQ(value, val);

}

TEST_F(RedisDAOTest, TestGet)
{
    TestGet();
}

TEST_F(RedisDAOTest, TestSet)
{
    TestSet();
}
