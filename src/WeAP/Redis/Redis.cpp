#include "Redis.h"
#include "RedisCommand.h"
#include "StringUtil.h"
#include "hiredis/hiredis.h"
#include "Logger.h"
#include "Error.h"
#include "Exception.h"

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

void Redis::Get(const string& key, string& value)
{
    string cmd = StringUtil::Format("GET %s", key.c_str());
    this->ExecuteCommand4Str(cmd, value);
}

void Redis::GetRange(const string& key, int start, int end, string& value)
{
    string cmd = StringUtil::Format("GETRANGE %s %d %d", key.c_str(), start, end);
    this->ExecuteCommand4Str(cmd, value);
}

int Redis::GetLength(const string& key)
{
    string cmd = StringUtil::Format("STRLEN %s", key.c_str());
    int64_t length;
    this->ExecuteCommand4Int(cmd, length);
    return length;
}


void Redis::GetSet(const string& key, const string& newValue, string& oldValue)
{
    string cmd = StringUtil::Format("GETSET %s %s", key.c_str(), newValue.c_str());
    this->ExecuteCommand4Str(cmd, oldValue);
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

bool Redis::Set(const string& key, const string& value, const string& EXorPX, int exprire, const string& NXorEX)
{
    string cmd = StringUtil::Format("SET %s %s", key.c_str(), value.c_str());
    if (EXorPX == "EX")
    {
        cmd += " EX " + std::to_string(exprire); //设置指定的到期时间(以秒为单位)。
    }
    else if (EXorPX == "PX")
    {
        cmd += " PX " + std::to_string(exprire);  //设置指定的到期时间(以毫秒为单位)。
    }

    if (NXorEX == "NX")
    {
        cmd += " NX";  //仅在键不存在时设置键。
    }
    else if (NXorEX == "EX")
    {
        cmd += " EX";  //只有在键已存在时才设置
    }

    string resp;
    this->ExecuteCommand4Status(cmd, resp);

    if (resp == "OK")
    {
        return true;
    }
    else
    {
        ERROR("redis Set failed, err:%s", resp.c_str());
        return false;
    }


}




bool Redis::SetNX(const string& key, const string& value)
{
    string cmd = StringUtil::Format("SETNX %s %s", key.c_str(), value.c_str());

    int64_t ret;
    this->ExecuteCommand4Int(cmd, ret);
    if (ret == 1L)
    {
        return true;
    }
    else if (ret == 0L)
    {
        return false;
    }

    return false;
}

void Redis::SetEx(const string& key, const string& value, int expireSenconds)
{
    string cmd = StringUtil::Format("SETEX %s %d %s", key.c_str(), expireSenconds, value.c_str());

    string resp;
    this->ExecuteCommand4Status(cmd, resp);

    if (resp != "OK")
    {
        ERROR("redis Set failed, err:%s", resp.c_str());
        throw Exception(Error::Redis_Set_Failed, "redis set err");
    }
}


void Redis::Append(const string& key, const string& value)
{
    string cmd = StringUtil::Format("APPEND %s %s", key.c_str(), value.c_str());
    int64_t ret;
    this->ExecuteCommand4Int(cmd, ret);
    if (ret != 1L)
    {
        ERROR("redis Del failed, ret:%lld", ret);
        throw Exception(Error::Redis_Append_Failed, "redis del err");
    }
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

int64_t Redis::Incr(const string& key)
{
    string cmd = StringUtil::Format("INCR %s", key.c_str());

    int64_t val;
    this->ExecuteCommand4Int(cmd, val);
    
    return val;
}

int64_t Redis::IncrBy(const string& key, int step)
{
    string cmd = StringUtil::Format("INCRBY %s %d", key.c_str(), step);

    int64_t val;
    this->ExecuteCommand4Int(cmd, val);
    
    return val;
}

int64_t Redis::Decr(const string& key)
{
    string cmd = StringUtil::Format("DECR %s", key.c_str());

    int64_t val;
    this->ExecuteCommand4Int(cmd, val);
    
    return val;
}

int64_t Redis::DecrBy(const string& key, int step)
{
    string cmd = StringUtil::Format("DECRBY %s %d", key.c_str(), step);

    int64_t val;
    this->ExecuteCommand4Int(cmd, val);
    
    return val;
}

void Redis::MSet(const vector<string>& keyList, const vector<string>& valList)
{
    string keyVals;
    for (size_t i= 0; i < keyList.size(); i++)
    {
        keyVals += keyList[i];
        keyVals += " ";
        keyVals += valList[i];
        keyVals += " ";
    }

    string cmd = StringUtil::Format("MSET %s ", keyVals.c_str());

    string resp;
    this->ExecuteCommand4Status(cmd, resp);
    //if (resp != "")
    //{
    //}

}

void Redis::MGet(const vector<string>& keyList, vector<string>& valList)
{
    string keys;
    for (size_t i= 0; i < keyList.size(); i++)
    {
        keys += keyList[i];
        keys += " ";
    }

    string cmd = StringUtil::Format("MGET %s ", keys.c_str());

    this->ExecuteCommand4Array(cmd, valList);
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

void Redis::ExecuteCommand4Array(const string& cmd, vector<string>& list)
{
    this->Connect();

    try
    {
        RedisCommand redisCommand;
        redisCommand.Execute4Array(this->context, cmd, list);
    }
    catch(...)
    {
        this->Close();
        throw;
    }
}


}}