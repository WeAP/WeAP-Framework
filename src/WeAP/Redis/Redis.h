
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

    void Get(const string& key, string& value);
    void GetRange(const string& key, int start, int end, string& value); //substr
    int GetLength(const string& key);
    void GetSet(const string& key, const string& newValue, string& oldValue);
    void Set(const string& key, const string& value);
    bool Set(const string& key, const string& value, const string& EXorPX, int exprire, const string& NXorEX);
    bool SetNX(const string& key, const string& value);  //SET value if Not eXists key
    void SetEx(const string& key, const string& value, int expireSenconds);
    void Append(const string& key, const string& value);
    void Del(const string& key);
    bool Exists(const string& key);

    int64_t Incr(const string& key);
    int64_t IncrBy(const string& key, int step);
    int64_t Decr(const string& key);
    int64_t DecrBy(const string& key, int step);

    void MSet(const vector<string>& keyList, const vector<string>& valList);
    void MGet(const vector<string>& keyList, vector<string>& valList);


    void Ping();

protected:
    void Connect();
    void Close();

    void ExecuteCommand4Status(const string& cmd, string& resp);
    void ExecuteCommand4Int(const string& cmd, int64_t& out);
    void ExecuteCommand4Str(const string& cmd, string& out);
    void ExecuteCommand4Array(const string& cmd, vector<string>& list);

protected:
    redisContext* context;
    string host;
    int port;
    int timeout;
};

}}

#endif

