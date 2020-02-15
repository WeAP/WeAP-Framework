#include "WebClientTest.h"
#include "DateTime.h"
#include "HttpCURL.h"

using namespace WeAP::System;
using namespace WeAP::CURL;

WebClientTest::WebClientTest()
{
    WebClient::Init();

    this->webClient.Init("127.0.0.1", 80);
}

WebClientTest::~WebClientTest()
{

}

void WebClientTest::TestGet()
{
    string instr;
    string outstr;
    this->webClient.Get("/index.html", instr, outstr, false);
    cout << outstr << endl;
}
void WebClientTest::TestPost()
{

}

TEST_F(WebClientTest, TestGet)
{
    TestGet();
}

TEST_F(WebClientTest, TestPost)
{
    TestPost();
}
