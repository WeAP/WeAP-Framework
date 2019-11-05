
#include "Handler.h"



namespace WeAP { namespace Framework {



Handler::Handler()
{
}

Handler::Handler(const Handler& other)
{
    this->Init(other);
}

Handler::~Handler()
{
    this->Clear();
}

Handler& Handler::operator=(const Handler& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Handler::Init(const Handler& other)
{
    /// @todo impl
}

void Handler::Clear()
{
    /// @todo impl
}

void Handler::Dump()
{
    /// @todo impl
}

}}
