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
             //printf("Connection error: %s\n", this->context->errstr);
             this->Close();
         } 
         else 
         {
             //printf("Connection error: can't allocate redis context\n");
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
        //throw
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
        //throw
    }
}

void Redis::Set(const string& key, const string& value)
{
    string cmd = StringUtil::Format("SET %s %s", key.c_str(), value.c_str());

    string resp;
    this->ExecuteCommand4Status(cmd, resp);

    if (resp != "OK")
    {
        //throw Execute();
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
        //throw
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
        //throw 
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