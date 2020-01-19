
#ifndef __WeAP_Redis_H__
#define __WeAP_Redis_H__

#include "Object.h"
#include "hiredis/hiredis.h"

using namespace std;
using namespace WeAP::System;

namespace WeAP { namespace Redis {

/**
 *
 */
class Redis: public Object
{
public:
    Redis();
    virtual ~Redis();

    void Init(const std::string& host, int port, int timeout = 200);

    void HSet(const string& key, const string& value);
    void HGet(const string& key, string& value);
    void HDel(const string& key);

    void Set(const string& key, const string& value);
    void Get(const string& key, string& value);
    void Del(const string& key);
    bool Exists(const string& key);

    void Ping();

protected:
    void Connect();
    void Close();

    void ExecuteCommand4Status(const string& cmd, string& resp);

    void ExecuteCommand4Int(const string& cmd, int64_t& out);
    void ExecuteCommand4Str(const string& cmd, string& out);

protected:
    redisContext* context;
    string host;
    int port;
    int timeout;
};

}}

#endif

