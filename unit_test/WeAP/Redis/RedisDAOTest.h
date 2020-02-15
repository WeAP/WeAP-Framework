#ifndef __WeAP_RedisDAOTest_H__
#define __WeAP_RedisDAOTest_H__

#include "ObjectTest.h"
#include "RedisDAO.h"

using namespace WeAP::Redis;

class RedisDAOTest: public ObjectTest
{
public:
    RedisDAOTest();
    virtual ~RedisDAOTest();

    void TestGet();
    void TestSet();

    void TestIncr();
    

protected:

    RedisDAO redisDAO;

};



#endif //__WeAP_RedisDAOTest_H__
