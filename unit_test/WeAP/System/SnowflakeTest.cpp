#include "SnowflakeTest.h"
#include "Charset.h"
#include "StringUtil.h"
#include "Snowflake.h"
#include <bitset>

using namespace WeAP::System;


SnowflakeTest::SnowflakeTest()
{
}

SnowflakeTest::~SnowflakeTest()
{
 
}

void SnowflakeTest::TestNextId()
{
    //str = "财付通支付科技有限公司";
    //EXPECT_EQ(true, Charset::IsUTF8(str, true, true));

    Snowflake idWorker;
    idWorker.SetDataCenterId(12);
    idWorker.SetWorkerId(5);

    const size_t count = 20;

    for (size_t i = 0; i < count; i++)
    {
        int64_t id = idWorker.NextId64();
        //cout << id << endl;
        //cout<< bitset<64>(id) << endl;
        //sleep(1);
    }
    //std::cout << "generate " << count << " id elapsed: " << timer.elapsed() << "ms" << std::endl;

}


TEST_F(SnowflakeTest, TestNextId)
{
    TestNextId();
}

