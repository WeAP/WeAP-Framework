#include "WebClientTest.h"
#include "DateTime.h"
#include "HttpCURL.h"

using namespace WeAP::System;
using namespace WeAP::CURL;

WebClientTest::WebClientTest()
{
    //127.0.0.1:6379
    //this->webClient.Init("127.0.0.1", 6379);
}

WebClientTest::~WebClientTest()
{

}

void WebClientTest::TestGet()
{

}
void WebClientTest::TestPost()
{
    //HttpCURL curl;

}

TEST_F(WebClientTest, TestGet)
{
    TestGet();
}

TEST_F(WebClientTest, TestPost)
{
    TestPost();
}
