
#ifndef __WeAP_RedisCommand_H__
#define __WeAP_RedisCommand_H__

#include "Object.h"
#include "hiredis/hiredis.h"

using namespace std;
using namespace WeAP::System;

namespace WeAP { namespace Redis {

/**
 *
 */
class RedisCommand: public Object
{
public:
    RedisCommand();
    virtual ~RedisCommand();

    void Execute4Status(redisContext* context, const string& cmd, string& resp);
    void Execute4Int(redisContext* context, const string& cmd, int64_t& resp);
    void Execute4Str(redisContext* context, const string& cmd, string& resp);

protected:
    void Execute(redisContext* context, const string& cmd);

protected:
    redisReply* reply;
};

}}

#endif

