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


void RedisDAO::Get(const string& key, string& value)
{
    this->redis.Get(key, value);
}

void RedisDAO::Set(const string& key, const string& value)
{
    this->redis.Set(key, value);
}

void RedisDAO::Del(const string& key)
{
    this->redis.Del(key);
}

void RedisDAO::Exists(const string& key)
{
    this->redis.Exists(key);
}

}}