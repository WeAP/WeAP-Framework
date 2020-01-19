#include "RedisCommand.h"
#include "Logger.h"

namespace WeAP { namespace Redis {


RedisCommand::RedisCommand()
{
    this->reply = NULL;
}

RedisCommand::~RedisCommand()
{
    if (this->reply)
    {
        ::freeReplyObject(this->reply);
        this->reply = NULL;
    }
}

void RedisCommand::Execute4Status(redisContext* context, const string& cmd, string& resp)
{
    this->Execute(context, cmd);

    if (this->reply->type != REDIS_REPLY_STATUS)
    {
        //throw Execute();
    }

    resp.assign(reply->str, reply->len);

}

void RedisCommand::Execute4Int(redisContext* context, const string& cmd, int64_t& resp)
{
    this->Execute(context, cmd);

    if (this->reply->type != REDIS_REPLY_INTEGER)
    {
        //throw
    }
    resp = this->reply->integer;
}

void RedisCommand::Execute4Str(redisContext* context, const string& cmd, string& resp)
{
    this->Execute(context, cmd);

    if (this->reply->type != REDIS_REPLY_STRING)
    {
        //throw Execute()
    }
    resp.assign(reply->str, reply->len);
}

void RedisCommand::Execute(redisContext* context, const string& cmd)
{
    if (this->reply)
    {
        ::freeReplyObject(this->reply);
        this->reply = NULL;
    }

    this->reply = (redisReply*)::redisCommand(context, cmd.c_str());
    if (this->reply == NULL)
    {
        //throw Execute();

        ERROR("redis cmd:%s, reply null", cmd.c_str());
    }

    INFO("redis cmd:%s, reply str:%s", cmd.c_str(), this->reply->str);

}


}}