#include "RedisDAO.h"


namespace WeAP { namespace Redis {


RedisDAO::RedisDAO()
{
}

RedisDAO::~RedisDAO()
{
}

void RedisDAO::Init(const INIConfig& config, const string& section)
{
    const KVMap& kvmap = config.GetSection(section);
    this->host = kvmap.GetString("Host");
    this->port = kvmap.GetInt32("Port");
    this->timeout = kvmap.GetInt32("Timeout");

    this->redis.Init(this->host, this->port, this->timeout);

}

void RedisDAO::Init(const std::string& host, int port)
{
    this->redis.Init(host, port);
}



string RedisDAO::GenerateNO(const string& key)
{
    int64_t no = this->redis.Incr(key);

    string str = StringUtil::Format("%06d", (int)no);

    return str;
}

bool RedisDAO::Lock(const string& key, const string& val, int lockms)
{
    return this->redis.Set(key, val, "PX", lockms, "NX");
}

void RedisDAO::Unlock(const string& key, const string& val)
{
    string val1;
    this->redis.Get(key, val1);
    if (val == val1)
    {
        this->redis.Del(key);
    }
}

void RedisDAO::Get(const string& key, string& value)
{
    this->redis.Get(key, value);
}

void RedisDAO::Set(const string& key, const string& value)
{
    this->redis.Set(key, value);
}

void RedisDAO::Append(const string& key, const string& value)
{
    this->redis.Append(key, value);
}

void RedisDAO::Del(const string& key)
{
    this->redis.Del(key);
}

void RedisDAO::Exists(const string& key)
{
    this->redis.Exists(key);
}

int64_t RedisDAO::Incr(const string& key)
{
    return this->redis.Incr(key);
}

int64_t RedisDAO::IncrBy(const string& key, int step)
{
    return this->redis.IncrBy(key, step);
}

}}