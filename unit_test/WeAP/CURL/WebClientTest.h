#ifndef __WeAP_WebClientTest_H__
#define __WeAP_WebClientTest_H__

#include "ObjectTest.h"
#include "WebClient.h"

using namespace WeAP::CURL;

class WebClientTest: public ObjectTest
{
public:
    WebClientTest();
    virtual ~WebClientTest();

    void TestGet();
    void TestPost();

protected:

    WebClient webClient;

};



#endif //__WeAP_WebClientTest_H__
