
#ifndef __WeAP_WebClient_H__
#define __WeAP_WebClient_H__

#include "curl/curl.h"

using namespace WeAP::System;
using namespace WeAP::Framework;

namespace WeAP {  namespace CURL  {


/**
 * https://blog.csdn.net/u011857683/article/details/53046295/
 */
class HttpCURL: public Object
{
public:
    HttpCURL();
    virtual ~HttpCURL();

    void Init(const string& host, int port = 80, int timeout = 2000, int connTimeout = 2000, const string& user = "", const string& pwd = "");

    void AppendHeader(const map<string, string>& headers);
    void AppendHeader(const string&  name, const string& val);
    

    void GET(const string& url, const string& instr, string& outstr, bool https);
    void POST(const string& url, const string& instr, string& outstr, bool https);

protected:

    void Perform(const string& url, const string& instr, string& outstr);

    void SetHeaders();

    void SetCookie(const string& cookie);
    void GetCookies(vector<string>& cookies);

    void SetReferer(const string& referer);

    void SetOpt4Https();

    int GetTotalTime();

    void Assert4SetOpt(CURLcode code, const string& option);
    void Assert4GetInfo(CURLcode code, const string& info);

    void Close();

    string GetLastError() const;

protected:
    CURL* curl;

    struct curl_slist* header;
    char errbuff[CURL_ERROR_SIZE] = {0};

};

}}

#endif

