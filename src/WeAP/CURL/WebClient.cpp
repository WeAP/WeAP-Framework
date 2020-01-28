
#include "WebClient.h"
#include "Convert.h"
#include "Logger.h"

namespace WeAP {  namespace CURL  {


int ReceiveData(char *data, size_t size, size_t nmemb,std::string *outstr)
{
    if (outstr == NULL)
    {
        return 0;
    }

    outstr->append(data, size * nmemb);

    return size * nmemb;
}


WebClient::Init()
{
    int ret = curl_global_init(CURL_GLOBAL_ALL);
    if(ret != CURLE_OK)
    {
        throw Exception(Error::CURL_Init_Failed, "curl_global_init failed");
    }
}

WebClient::Cleanup()
{
    int ret = curl_global_cleanup();
}
    

WebClient::WebClient() 
{
    this->curl = NULL;
    this->headers = NULL;

    this->timeout = 2; //默认超时时间设置为2s

}

WebClient::~WebClient() 
{
    this->Close();
}

void WebClient::Init(const INIConfig& config , const string& section)
{
    const KVMap& kvmap = config.GetSection(section);
    this->host = kvmap.GetString("Host");
    this->port = kvmap.GetInt32("Port");
    this->timeout = kvmap.GetInt32("Timeout");
    this->connTimeout = kvmap.GetInt32("ConnTimeout");
    this->user = kvmap.GetString("User");
    this->pwd = kvmap.GetString("Pwd");

}

void WebClient::Init(const string &host, 
                     int port, 
                     int connTimeout, 
                     int timeout,
                     const string& user,
                     const string& pwd)
{
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


void WebClient::GET(const string& path, const string& instr, string& outstr, bool https)
{
    this->Close();

    try
    {    
        string url = StringUtil::Format("https://%s:%d//%s?%s", 
                                        this->host.c_str(), 
                                        this->port, 
                                        path.c_str(),
                                        instr.c_str());    
        this->Init4Request(url);

        CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_HTTPGET, 1);
        this->Assert4SetOpt(ret, "CURLOPT_HTTPGET");

        ret = curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, ReceiveData);
        this->Assert4SetOpt(ret, "CURLOPT_WRITEFUNCTION");

        ret = curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &outstr);
        this->Assert4SetOpt(ret, "CURLOPT_WRITEDATA");

        if (https)
        {
            this->SetOpt4Https();
        }
        this->Perform();

        this->Close();

    }
    catch(...)
    {
        this->Close();
        throw;
    }

}


void WebClient::POST(const string& path, const string& instr, string& outstr, bool https)
{
    this->Close();

    try
    {    
        string url = StringUtil::Format("https://%s:%d//%s", 
                                        this->host.c_str(), 
                                        this->port, 
                                        path.c_str());

        this->Init4Request(url);

        //发送数据,以及发送方式
        CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_POST, 1);
        this->this->Assert4SetOpt(code, "CURLOPT_POST");

        ret = curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, instr.c_str());
        this->Assert4SetOpt(ret, "CURLOPT_POSTFIELDS");


        ret = curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, ReceiveData);
        this->Assert4SetOpt(ret, "CURLOPT_WRITEFUNCTION");

        ret = curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &outstr);
        this->Assert4SetOpt(ret, "CURLOPT_WRITEDATA");

        if (https)
        {
            this->SetOpt4Https();
        }

        this->Perform();

        this->Close();
    }
    catch(...)
    {
        this->Close();
        throw;
    }

}


void WebClient::AppendHeader(const string&  name, const string& val)
{
    if (name.empty() || val.empty())
    {
        return;
    }

    string item = name + ": " + val;
    this->header = curl_slist_append(this->header, item.c_str());
    if (this->header == NULL)
    {
        throw Exception(Error::CURL_Append_Header_NULL, "append header return null.")
    }
}

void WebClient::SetHeaders()
{
    if (this->header == NULL)
    {
        return;
    }

    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    this->Assert4SetOpt(ret, "CURLOPT_HTTPHEADER");
}

void WebClient::SetCookie(const string& cookie)
{
    if(cookie.empty())
    {
        return;
    }
    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_COOKIE, cookie.c_str());
    this->Assert4SetOpt(ret, "CURLOPT_COOKIE");
}

void WebClient::GetCookies(vector<string>& cookies)
{
    struct curl_slist *cookieList;

    CURLcode ret = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookieList);
    this->Assert4GetInfo(ret, "CURLINFO_COOKIELIST");

    struct curl_slist* pCookie = cookieList;

    while (pCookie)
    {
        cookies.push_back(pCookie->data)
        pCookie = pCookie->next;
    }

    curl_slist_free_all(cookieList);
}

void WebClient::SetReferer(const string& referer)
{
    if (referer.empty())
    {
        return;
    }

    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_REFERER, refer.c_str());
    this->Assert4SetOpt(ret, "CURLOPT_REFERER");

}

void WebClient::SetOpt4Https()
{
    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    this->Assert4SetOpt(ret, "CURLOPT_SSL_VERIFYPEER");

    ret = curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYHOST, 0L);
    this->Assert4SetOpt(ret, "CURLOPT_SSL_VERIFYHOST");
        //curl_easy_setopt(conn, CURLOPT_SSLVERSION, CURL_SSLVERSION_DEFAULT);
}

int WebClient::GetTotalTime()
{
    int totalTime = 0;
    CURLcode ret = curl_easy_getinfo(this->curl, CURLINFO_TOTAL_TIME, &totalTime);
    this->Assert4GetInfo(code, "CURLINFO_TOTAL_TIME");
    return totalTime;
}

void WebClient::Init4Request(const strng& url)
{
    this->curl = curl_easy_init();
    if (this->curl == NULL)
    {
        ERROR("curl_easy_init failed to create CURL");    
        throw Exception(Error::CURL_Init_Failed, "curl_easy_init failed to create CURL");
    }
    
    CURLcode code = curl_easy_setopt(this->curl, CURLOPT_ERRORBUFFER, errbuff);
    this->Assert4SetOpt(code, "CURLOPT_ERRORBUFFER");

    code = curl_easy_setopt(this->curl, CURLOPT_URL, (char*)url.c_str());
    this->Assert4SetOpt(code, "CURLOPT_URL");

    code = curl_easy_setopt(this->curl, CURLOPT_PORT, this->port);
    this->Assert4SetOpt(code, "CURLOPT_PORT");

    code = curl_easy_setopt(this->curl, CURLOPT_CONNECTTIMEOUT, this->connTimeout);
    this->Assert4SetOpt(code, "CURLOPT_CONNECTTIMEOUT");
    

    code = curl_easy_setopt(this->curl, CURLOPT_TIMEOUT, this->timeout);
    this->Assert4SetOpt(code, "CURLOPT_TIMEOUT");


    if((!(this->user.empty())) && (!(this->pwd.empty())))
    {
        string userPwd = this->user + ":" + this->pwd;
        code = curl_easy_setopt(this->curl, CURLOPT_USERPWD, (char*)userPwd.c_str());
        this->Assert4SetOpt(code, "CURLOPT_FAILONERROR");

    }

    code = curl_easy_setopt(this->curl, CURLOPT_FAILONERROR, true);
    this->Assert4SetOpt(code, "CURLOPT_FAILONERROR");

    //禁用掉alarm这种超时
    code = curl_easy_setopt(this->curl, CURLOPT_NOSIGNAL, 1);
    this->Assert4SetOpt(code, "CURLOPT_NOSIGNAL");

    /*
    第一:默认情况下libcurl完成一个任务以后，出于重用连接的考虑不会马上关闭,如果每次目标主机不一样，这里禁止重连接
    第二:每次执行完curl_easy_perform，licurl会继续保持与服务器的连接。接下来的请求可以使用这个连接而不必创建新的连接,如果目标主机是同一个的话。
    这样可以减少网络开销。
    */
    //code = curl_easy_setopt(this->curl, CURLOPT_FORBID_REUSE, 1);
    //this->Assert4SetOpt(code, "CURLOPT_FORBID_REUSE");

    this->SetHeaders();

}


void WebClient::Perform()
{
    CURLcode ret = curl_easy_perform(this->curl);
     
    //http返回码
    long httpCode = 0;
    CURLcode retGetInfo = curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &httpCode);
 
    if(CURLE_OK != ret || 200 != httpCode)
    {
        const char* errMsg = curl_easy_strerror(ret);

        //curl传送失败
        if(CURLE_OPERATION_TIMEOUTE == ret)
        {
            throw Exception(Error::CURL_Perform_Timeout, "curl perform timeout")
        }
        else
        {
            throw Exception(Error::CURL_Perform_Failed, "curl perform failed")
        }

    }

}


void WebClient::Assert4SetOpt(CURLcode ret, const string& option)
{
    if (ret == CURLE_OK)
    {
        return;
    }

    string errMsg = StringUtil::Format("curl_easy_setopt: %s, ret: %d, err:%s",
                                        option.c_str(),
                                        ret,
                                        curl_easy_strerror(ret));

    ERROR("%s", errMsg.c_str());
    throw Exception(Error::CURL_Setopt_Failed, errMsg);

}


void WebClient::Assert4GetInfo(CURLcode ret, const string& info)
{
    if (ret == CURLE_OK)
    {
        return;
    }

    string errMsg = StringUtil::Format("curl_easy_getinfo: %s, ret: %d, err:%s",
                                        info.c_str(),
                                        ret,
                                        curl_easy_strerror(ret));
   
    ERROR("%s", errMsg.c_str());
    throw Exception(Error::CURL_GetInfo_Failed, errMsg);

}

void WebClient::Close()
{
    if (this->curl != NULL)
    {
        curl_easy_cleanup(this->curl);
        this->curl = NULL;
    }

    if (this->header != NULL)
    {
        curl_slist_free_all(this->header);
        this->header = NULL;
    }
}


}}


