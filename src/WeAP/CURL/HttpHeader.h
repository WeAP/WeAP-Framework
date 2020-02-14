#ifndef __WeAP_HttpHeader_H__
#define __WeAP_HttpHeader_H__

#include "curl/curl.h"
#include "AppObject.h"

using namespace WeAP::System;
using namespace WeAP::Framework;

namespace WeAP { namespace CURL {
/*
class HttpHeader: public AppObject
{
public:
    HttpHeader(CURL* curl);
    virtual ~HttpHeader();

    void Append(const string&  name, const string& val);
    void SetHeaders();

protected:
    CURL* curl;
    struct curl_slist* header;

};
*/
}}

#endif

