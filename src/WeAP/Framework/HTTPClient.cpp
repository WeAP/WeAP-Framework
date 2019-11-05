
#include "HTTPClient.h"



namespace WeAP { namespace Framework {



HTTPClient::HTTPClient()
{
}

HTTPClient::HTTPClient(const HTTPClient& other)
{
    this->Init(other);
}

HTTPClient::~HTTPClient()
{
    this->Clear();
}

HTTPClient& HTTPClient::operator=(const HTTPClient& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void HTTPClient::Init(const HTTPClient& other)
{
    /// @todo impl
}

void HTTPClient::Clear()
{
    /// @todo impl
}

void HTTPClient::Dump()
{
    /// @todo impl
}

}}
