
#include "Client.h"



namespace WeAP { namespace Framework {



Client::Client()
{
}

Client::Client(const Client& other)
{
    this->Init(other);
}

Client::~Client()
{
    this->Clear();
}

Client& Client::operator=(const Client& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Client::Init(const Client& other)
{
    /// @todo impl
}

void Client::Clear()
{
    /// @todo impl
}

void Client::Dump()
{
    /// @todo impl
}

}}
