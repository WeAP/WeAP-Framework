
#ifndef __WeAP_WebClient_H__
#define __WeAP_WebClient_H__

#include "curl/curl.h"


#include "Logger.h"
#include "Client.h"
#include "INIConfig.h"


using namespace WeAP::System;
using namespace WeAP::Framework;


namespace WeAP {  namespace CURL  {


/**
 * https://blog.csdn.net/u011857683/article/details/53046295/
 */
class WebClient: public Client
{
public:
    static void Init();
    static void Cleanup();
    
    //回调函数，将返回缓存数据写出
    //static size_t ReceiveDate(void* buffer, size_t size, size_t nmemb, void* content);

public:

    WebClient();
    virtual ~WebClient();

    void Init(const INIConfig& config , const string& section);

    void Init(const string& host, 
              int port = 80, 
              int connTimeout = 1, 
              int timeout = 1,
              const string& user = "", 
              const strng& pwd = "");

    virtual void InitHeader(){};

    void GET(const string& path, const KVMap& inMap, KVMap& outMap, bool https = true, int tryTimes = 1);
    void POST(const string& path, const KVMap& inMap, KVMap& outMap, bool https = true, int tryTimes = 1);

    void GET(const string& path, const string& instr, const string& outstr, bool https = true);
    void POST(const string& path, const string& instr, const string& outstr, bool https = true);

protected:
    void AppendHeader(const string&  name, const string& val);
    void SetHeaders();

    void SetCookie(const string& cookie);
    void GetCookies(vector<string>& cookies);

    void SetReferer(const string& referer);

    void SetOpt4Https();

    int GetTotalTime();

    void Init4Request(const strng& url);

    void Assert4SetOpt(CURLcode code, const string& option);

    void Assert4GetInfo(CURLcode code, const string& info);

    void Perform();

    void Close();

protected:
    CURL* curl;

    string host;
    int port;
    int timeout;
    int connTimeout;
    string user;
    string pwd;

    struct curl_slist* header;
    char errbuff[CURL_ERROR_SIZE] = {0};

};

}}

#endif

