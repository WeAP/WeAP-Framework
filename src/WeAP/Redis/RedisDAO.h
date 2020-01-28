
#ifndef __WeAP_RedisDAO_H__
#define __WeAP_RedisDAO_H__

#include "DAO.h"
#include "Redis.h"
#include "INIConfig.h"

using namespace std;
using namespace WeAP::System;
using namespace WeAP::Framework;

namespace WeAP { namespace Redis {

/**
 *
 */
class RedisDAO: public DAO
{
public:
    RedisDAO();
    virtual ~RedisDAO();

    void Init(const INIConfig& config, const string& section);

    void Init(const std::string& host, int port);

    void Get(const string& key, string& value);
    void Set(const string& key, const string& value);
    void Del(const string& key);
    void Exists(const string& key);

protected:
    Redis redis;

    string host;
    int port;
    int timeout;
};

}}

#endif

