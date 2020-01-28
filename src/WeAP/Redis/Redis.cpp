#include "Redis.h"
#include "RedisCommand.h"
#include "StringUtil.h"
#include "hiredis/hiredis.h"


namespace WeAP { namespace Redis {


Redis::Redis()
{
    this->context = NULL;
}

Redis::~Redis()
{
    this->Close();
}

void Redis::Init(const std::string& host, int port, int timeout)
{
    this->host = host;
    this->port = port;
    this->timeout = timeout;

    this->Connect();
}

void Redis::Connect()
{
    if (this->context != NULL)
    {
        return;
    }

    struct timeval tvTimeout;
    tvTimeout.tv_sec = this->timeout / 1000;  
    tvTimeout.tv_usec = (this->timeout % 1000) * 1000;

    this->context = ::redisConnectWithTimeout(this->host.c_str(), this->port, tvTimeout);
    if (this->context == NULL || this->context->err) 
    {
         if (this->context) 
         {
             ERROR("Connection error: %s", this->context->errstr);
             this->Close();
             throw Exception(Error::Redis_Connect_Failed, "redis connect failed.");

         } 
         else 
         {
             ERROR("Connection error: can't allocate redis context");
             throw Exception(Error::Redis_Context_Is_NULL, "can't allocate redis context.");
         }

    }
}

void Redis::Close()
{
    if (this->context)
    {
        ::redisFree(this->context);
        this->context = NULL;
    }
}

void Redis::HSet(const string& key, const string& value)
{
    string cmd = StringUtil::Format("HSET %s %s", key.c_str(), value.c_str());
    int64_t ret;
    this->ExecuteCommand4Int(cmd, ret);
    if (ret != 1L)
    {
        ERROR("redis HSet failed, ret:%lld", ret);
        throw Exception(Error::Redis_HSet_Failed, "redis Hdel err");
    }
}

void Redis::HGet(const string& key, string& value)
{
    string cmd = StringUtil::Format("HGET %s", key.c_str());

    this->ExecuteCommand4Str(cmd, value);
}

void Redis::HDel(const string& key)
{
    string cmd = StringUtil::Format("HDEL %s", key.c_str());
    int64_t ret;
    this->ExecuteCommand4Int(cmd, ret);
    if (ret != 1L)
    {
        ERROR("redis HDel failed, ret:%lld", ret);
        throw Exception(Error::Redis_HDel_Failed, "redis Hdel err");
    }
}

void Redis::Set(const string& key, const string& value)
{
    string cmd = StringUtil::Format("SET %s %s", key.c_str(), value.c_str());

    string resp;
    this->ExecuteCommand4Status(cmd, resp);

    if (resp != "OK")
    {
        ERROR("redis Set failed, err:%s", resp.c_str());
        throw Exception(Error::Redis_Set_Failed, "redis set err");
    }

}

void Redis::Get(const string& key, string& value)
{
    string cmd = StringUtil::Format("GET %s", key.c_str());
    this->ExecuteCommand4Str(cmd, value);
}

void Redis::Del(const string& key)
{
    string cmd = StringUtil::Format("DEL %s", key.c_str());
    int64_t ret;
    this->ExecuteCommand4Int(cmd, ret);
    if (ret != 1L)
    {
        ERROR("redis Del failed, ret:%lld", ret);
        throw Exception(Error::Redis_HDel_Failed, "redis del err");
    }

}
bool Redis::Exists(const string& key)
{
    string cmd = StringUtil::Format("exists %s", key.c_str());

    int64_t ret;
    this->ExecuteCommand4Int(cmd, ret);
    if (ret != 1L)
    {
        return false;
    }
    return true;
}

void Redis::Ping()
{
    this->Connect();
    string cmd = "PING";
    string resp;
    this->ExecuteCommand4Status(cmd, resp);
    if (resp != "PONG")
    {
        ERROR("redis ping failed, err:%s", resp.c_str());
        throw Exception(Error::Redis_Ping_Failed, "redis set err");
    }
}

void Redis::ExecuteCommand4Status(const string& cmd, string& resp)
{
    this->Connect();

    try
    {
        RedisCommand redisCommand;
        redisCommand.Execute4Status(this->context, cmd, resp);
    }
    catch(...)
    {
        this->Close();
        throw;
    }
}

void Redis::ExecuteCommand4Int(const string& cmd, int64_t& out)
{
    this->Connect();

    try
    {
        RedisCommand redisCommand;
        redisCommand.Execute4Int(this->context, cmd, out);
    }
    catch(...)
    {
        this->Close();
        throw;
    }
}

void Redis::ExecuteCommand4Str(const string& cmd, string& out)
{
    this->Connect();

    try
    {
        RedisCommand redisCommand;
        redisCommand.Execute4Str(this->context, cmd, out);
    }
    catch(...)
    {
        this->Close();
        throw;
    }
}


}}