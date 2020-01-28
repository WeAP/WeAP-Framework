#include "HttpHeader.h"
#include "Exception.h"
#include "Error.h"

using namespace WeAP::System;

namespace WeAP { namespace CURL {

HttpHeader::HttpHeader(CURL* curl)
{
    this->curl = curl;
    this->header = NULL;
}

HttpHeader::~HttpHeader()
{
    if (this->header != NULL)
    {
        curl_slist_free_all(this->header);
        this->header = NULL;
    }
}


void HttpHeader::Append(const string&  name, const string& val)
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

void HttpHeader::SetHeaders()
{
    if (this->header == NULL)
    {
        return;
    }

    CURLcode ret = curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    this->Assert4SetOpt(ret, "CURLOPT_HTTPHEADER");
}



}}

