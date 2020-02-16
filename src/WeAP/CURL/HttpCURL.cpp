
#include "HttpCURL.h"
#include "Logger.h"
#include "Error.h"
#include "Exception.h"

namespace WeAP {  namespace CURL  {


int ReceiveData(char* data, size_t size, size_t nmemb,  void* userdata)
{
    if (userdata == NULL)
    {
        return 0;
    }

    string* outstr = (string*)userdata;
    outstr->append(data, size * nmemb);

    return size * nmemb;
}


HttpCURL::HttpCURL() 
{
    this->curl = curl_easy_init();
}

HttpCURL::~HttpCURL() 
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

void HttpCURL::Init(const string& host, int port, int timeout, int connTimeout, const string& user, const string& pwd)
{
    if (this->curl == NULL)
    {
        ERROR("curl_easy_init failed to create CURL");    
        throw Exception(Error::CURL_Init_Failed, "curl_easy_init failed to create CURL");
    }

    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_ERRORBUFFER, errbuff);
    this->Assert4SetOpt(ret, "CURLOPT_ERRORBUFFER");

    ret = curl_easy_setopt(this->curl, CURLOPT_PORT, port);
    this->Assert4SetOpt(ret, "CURLOPT_PORT");

    ret = curl_easy_setopt(this->curl, CURLOPT_CONNECTTIMEOUT_MS, (long)connTimeout);
    this->Assert4SetOpt(ret, "CURLOPT_CONNECTTIMEOUT");
    
    ret = curl_easy_setopt(this->curl, CURLOPT_TIMEOUT_MS, (long)timeout);
    this->Assert4SetOpt(ret, "CURLOPT_TIMEOUT");

    if((!user.empty()) && (!pwd.empty()))
    {
        string userPwd = user + ":" + pwd;
        ret = curl_easy_setopt(this->curl, CURLOPT_USERPWD, (char*)userPwd.c_str());
        this->Assert4SetOpt(ret, "CURLOPT_FAILONERROR");
    }

    ret = curl_easy_setopt(this->curl, CURLOPT_FAILONERROR, true);
    this->Assert4SetOpt(ret, "CURLOPT_FAILONERROR");

    //禁用掉alarm这种超时
    ret = curl_easy_setopt(this->curl, CURLOPT_NOSIGNAL, 1);
    this->Assert4SetOpt(ret, "CURLOPT_NOSIGNAL");

    ret = curl_easy_setopt(this->curl, CURLOPT_NOPROGRESS, 1L); //默认为1, 设置该值为非零值关闭CRUL传输显示的进度条，为0表示打开。
    this->Assert4SetOpt(ret, "CURLOPT_NOPROGRESS");

    ret = curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 0L);  //输出通信过程中的一些细节
    this->Assert4SetOpt(ret, "CURLOPT_VERBOSE");

    ret = curl_easy_setopt(this->curl, CURLOPT_HEADER, 0L);  //输出header
    this->Assert4SetOpt(ret, "CURLOPT_HEADER");
    //ret = curl_easy_setopt(this->curl, CURLOPT_HEADERFUNCTION, ReceiveHttpHeader);
    //this->Assert4SetOpt(ret, "CURLOPT_HEADERFUNCTION");
    //ret = curl_easy_setopt(this->curl, CURLOPT_HEADERDATA, &this->respHeader);
    //this->Assert4SetOpt(ret, "CURLOPT_HEADERDATA");

    //ret = curl_easy_setopt(this->curl, CURLOPT_FOLLOWLOCATION, 1L); //设为0，则不会自动301，302跳转；
    //this->Assert4SetOpt(ret, "CURLOPT_FOLLOWLOCATION");

    //ret = curl_easy_setopt(this->curl, CURLOPT_NOBODY, 0L);  //输出中不包含body部分
    //this->Assert4SetOpt(ret, "CURLOPT_NOBODY");
    


    /*
    第一:默认情况下libcurl完成一个任务以后，出于重用连接的考虑不会马上关闭,如果每次目标主机不一样，这里禁止重连接
    第二:每次执行完curl_easy_perform，licurl会继续保持与服务器的连接。接下来的请求可以使用这个连接而不必创建新的连接,如果目标主机是同一个的话。
    这样可以减少网络开销。
    */
    ret = curl_easy_setopt(this->curl, CURLOPT_FORBID_REUSE, 1);
    this->Assert4SetOpt(ret, "CURLOPT_FORBID_REUSE");

}


void HttpCURL::Get(const string& url, const string& instr, string& outstr, bool https)
{
    this->SetHeaders();

    string getUrl = url;
    if (!instr.empty())
    {
        getUrl += "?" + instr;
    }

    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_URL, (char*)getUrl.c_str());
    this->Assert4SetOpt(ret, "CURLOPT_URL");

    ret = curl_easy_setopt(this->curl, CURLOPT_HTTPGET, 1);
    this->Assert4SetOpt(ret, "CURLOPT_HTTPGET");

    ret = curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, ReceiveData);
    this->Assert4SetOpt(ret, "CURLOPT_WRITEFUNCTION");

    ret = curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &outstr);
    this->Assert4SetOpt(ret, "CURLOPT_WRITEDATA");

    if (https)
    {
        this->SetOpt4Https();
    }

    this->Perform(url, instr, outstr);
}


void HttpCURL::Post(const string& url, const string& instr, string& outstr, bool https)
{
    this->SetHeaders();

    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_URL, (char*)url.c_str());
    this->Assert4SetOpt(ret, "CURLOPT_URL");

    //发送数据,以及发送方式
    ret = curl_easy_setopt(this->curl, CURLOPT_POST, 1);
    this->Assert4SetOpt(ret, "CURLOPT_POST");

    ret = curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, const_cast<char *>(instr.c_str()));
    this->Assert4SetOpt(ret, "CURLOPT_POSTFIELDS");

    ret = curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, instr.size());
    this->Assert4SetOpt(ret, "CURLOPT_POSTFIELDSIZE");

    ret = curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, ReceiveData);
    this->Assert4SetOpt(ret, "CURLOPT_WRITEFUNCTION");

    ret = curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &outstr);
    this->Assert4SetOpt(ret, "CURLOPT_WRITEDATA");

    if (https)
    {
        this->SetOpt4Https();
    }

    this->Perform(url, instr, outstr);
}


void HttpCURL::Perform(const string& url, const string& instr, string& outstr)
{
    CURLcode ret = curl_easy_perform(this->curl);
     
    //http返回码
    long httpCode = 0;
    CURLcode getinfoRet = curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &httpCode);
    if (getinfoRet != CURLE_OK)
    {
        WARN("curl_easy_getinfo:CURLINFO_RESPONSE_CODE, ret:%d", getinfoRet);
    }
 
    if(CURLE_OK != ret || 200 != httpCode)
    {
        const char* errMsg = curl_easy_strerror(ret);

        ERROR("url:%s, req:%s, resp:%s, cost:%d, err:%s", url.c_str(), instr.c_str(), outstr.c_str(), this->GetTotalTime(), errMsg);

        //curl传送失败
        if(CURLE_OPERATION_TIMEDOUT == ret)
        {
            throw Exception(Error::CURL_Perform_Timeout, "curl perform timeout");
        }        
        else if (ret == CURLE_UNSUPPORTED_PROTOCOL)
        {
            throw Exception(Error::CURL_Perform_Failed, "curl perform failed, unsupported protocol");
            //不支持的协议，由URL的头部指定
        }
        else if (ret == CURLE_COULDNT_CONNECT)
        {
            //不能连接到remote 主机或者代理
            throw Exception(Error::CURL_Perform_Failed, "curl perform failed, couldnt connect");
        }
        else if (ret == CURLE_REMOTE_ACCESS_DENIED)
        {
            //访问被拒绝
            throw Exception(Error::CURL_Perform_Failed, "curl perform failed, remote access denied");
        }
        else if (ret == CURLE_HTTP_RETURNED_ERROR)
        {
            //Http返回错误
            throw Exception(Error::CURL_Perform_Failed, "curl perform failed, http returned error");
        }
        
        else
        {
            throw Exception(Error::CURL_Perform_Failed, "curl perform failed");
        }

    }

    INFO("url:%s, req:%s, resp:%s, cost:%d", url.c_str(), instr.c_str(), outstr.c_str(), this->GetTotalTime());


}

void HttpCURL::AppendHeader(const map<string, string>& headers)
{
    for (auto it = headers.cbegin(); it != headers.cend(); it++) 
    {
        this->AppendHeader(it->first, it->second);
    }
}

void HttpCURL::AppendHeader(const string&  name, const string& val)
{
    if (name.empty() || val.empty())
    {
        return;
    }

    string item = name + ": " + val;
    this->header = curl_slist_append(this->header, item.c_str());
    if (this->header == NULL)
    {
        throw Exception(Error::CURL_Append_Header_NULL, "append header return null.");
    }

}

void HttpCURL::SetHeaders()
{
    if (this->header == NULL)
    {
        return;
    }

    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    this->Assert4SetOpt(ret, "CURLOPT_HTTPHEADER");
}

void HttpCURL::SetCookie(const string& cookie)
{
    if(cookie.empty())
    {
        return;
    }
    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_COOKIE, cookie.c_str());
    this->Assert4SetOpt(ret, "CURLOPT_COOKIE");
}

void HttpCURL::GetCookies(vector<string>& cookies)
{
    struct curl_slist *cookieList;

    CURLcode ret = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookieList);
    this->Assert4GetInfo(ret, "CURLINFO_COOKIELIST");

    struct curl_slist* pCookie = cookieList;

    while (pCookie)
    {
        cookies.push_back(pCookie->data);
        pCookie = pCookie->next;
    }

    curl_slist_free_all(cookieList);
}

void HttpCURL::SetReferer(const string& referer)
{
    if (referer.empty())
    {
        return;
    }

    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_REFERER, referer.c_str());
    this->Assert4SetOpt(ret, "CURLOPT_REFERER");

}

void HttpCURL::SetOpt4Https()
{
    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    this->Assert4SetOpt(ret, "CURLOPT_SSL_VERIFYPEER");

    ret = curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYHOST, 0L);
    this->Assert4SetOpt(ret, "CURLOPT_SSL_VERIFYHOST");
    //curl_easy_setopt(conn, CURLOPT_SSLVERSION, CURL_SSLVERSION_DEFAULT);
}

int HttpCURL::GetTotalTime()
{
    int totalTime = 0;
    CURLcode ret = curl_easy_getinfo(this->curl, CURLINFO_TOTAL_TIME, &totalTime);
    this->Assert4GetInfo(ret, "CURLINFO_TOTAL_TIME");
    return totalTime;
}

void HttpCURL::Assert4SetOpt(CURLcode ret, const string& option)
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


void HttpCURL::Assert4GetInfo(CURLcode ret, const string& info)
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


string HttpCURL::GetLastError() const
{
    return string(this->errbuff);
}

}}


