
#ifndef __WeAP_WebClient_H__
#define __WeAP_WebClient_H__

#include "curl/curl.h"
#include "Logger.h"
#include "Client.h"
#include "INIConfig.h"

using namespace WeAP::System;
using namespace WeAP::Framework;

namespace WeAP {  namespace CURL  {


class WebClient: public Client
{
public:
    static void Init();
    static void Cleanup();

public:

    WebClient();
    virtual ~WebClient();

    void Init(const INIConfig& config , const string& section);

    void Init(const string& host, 
              int port = 80, 
              int connTimeout = 2000, 
              int timeout = 2000,
              const string& user = "", 
              const strng& pwd = "");

    virtual void GET(const string& path, const KVMap& inMap, KVMap& outMap, bool https = true, int tryTimes = 1);
    virtual void POST(const string& path, const KVMap& inMap, KVMap& outMap, bool https = true, int tryTimes = 1);

    virtual void GET(const string& path, const string& instr, const string& outstr, bool https = true, int tryTimes = 1);
    virtual void POST(const string& path, const string& instr, const string& outstr, bool https = true, int tryTimes = 1);

protected:
    string host;
    int port;
    int timeout;
    int connTimeout;
    string user;
    string pwd;

};

}}

#endif

