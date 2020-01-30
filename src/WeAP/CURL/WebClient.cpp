
#include "WebClient.h"
#include "Convert.h"
#include "Logger.h"
#include "HttpCURL.h"

namespace WeAP {  namespace CURL  {


void WebClient::Init()
{
    static bool hasFinished = false;
    if (hasFinished)
    {
        return;
    }

    CURLcode ret = curl_global_init(CURL_GLOBAL_ALL);
    if(ret != CURLE_OK)
    {
        ERROR("curl_global_init failed, ret:%d", ret);
        throw Exception(Error::CURL_Init_Failed, "curl_global_init failed");
    }

    hasFinished = true;
    INFO("curl_global_init succ");
    
}

void WebClient::Cleanup()
{
    static bool hasFinished = false;
    if (hasFinished)
    {
        return;
    }

    CURLcode ret = curl_global_cleanup();
    if(ret != CURLE_OK)
    {
        INFO("curl_global_cleanup succ, ret:%d", ret);
        throw Exception(Error::CURL_Init_Failed, "curl_global_cleanup failed");
    }

    hasFinished = true;
    INFO("curl_global_cleanup succ");
}
    

WebClient::WebClient() 
{
    this->port = 80;
    this->timeout = 2000;
    this->connTimeout = 2000;
}

WebClient::~WebClient() 
{
}

void WebClient::Init(const INIConfig& config , const string& section)
{
    const KVMap& kvmap = config.GetSection(section);
    string host = kvmap.GetString("Host");
    int port = kvmap.GetInt32("Port");
    int timeout = kvmap.GetInt32("Timeout");
    int connTimeout = kvmap.GetInt32("ConnTimeout");
    string user = kvmap.GetString("User");
    string pwd = kvmap.GetString("Pwd");

    this->Init(host, port, connTimeout,  timeout, user, pwd);

}

void WebClient::Init(const string &host, 
                     int port, 
                     int connTimeout, 
                     int timeout,
                     const string& user,
                     const string& pwd)
{
    WebClient::Init();

    this->host = host;
    this->port = port;
    this->connTimeout = connTimeout;
    this->timeout = timeout;
    this->user = user;
    this->pwd = pwd;

}


void WebClient::GET(const string& path, const KVMap& inMap, KVMap& outMap, bool https, int tryTimes)
{
    string outstr;
    this->GET(path, inMap.ToUrlString(), outstr);
    outMap.Parse(outstr);
}
void WebClient::POST(const string& path, const KVMap& inMap, KVMap& outMap, bool https, int tryTimes)
{
    string outstr;
    this->POST(path, inMap.ToUrlString(), outstr);
    outMap.Parse(outstr);
}


void WebClient::GET(const string& path, const string& instr, string& outstr, bool https, int tryTimes)
{
    string url;
    if (https)
    {
        url = StringUtil::Format("http://%s:%d//%s", this->host.c_str(), this->port, path.c_str());
    }
    else
    {
        url = StringUtil::Format("https://%s:%d//%s", this->host.c_str(), this->port, path.c_str());
    }

    HttpCURL curl;
    curl.Init(this->host, this->port, this->timeout, this->connTimeout, this->user, this->pwd);
    curl.AppendHeader("Content-Type", "application/x-www-form-urlencoded;charset=UTF-8");
    
    curl.GET(url, instr, outstr, https);
}


void WebClient::POST(const string& path, const string& instr, string& outstr, bool https, int tryTimes)
{
    string url;
    if (https)
    {
        url = StringUtil::Format("http://%s:%d//%s", this->host.c_str(), this->port, path.c_str());
    }
    else
    {
        url = StringUtil::Format("https://%s:%d//%s", this->host.c_str(), this->port, path.c_str());
    }

    HttpCURL curl;
    curl.Init(this->host, this->port, this->timeout, this->connTimeout, this->user, this->pwd);
    curl.AppendHeader("Content-Type", "application/x-www-form-urlencoded;charset=UTF-8");
    curl.POST(url, instr, outstr, https);

}






}}


