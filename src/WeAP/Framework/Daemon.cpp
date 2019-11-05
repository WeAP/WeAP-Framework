
#include "Daemon.h"



namespace WeAP { namespace Framework {



Daemon::Daemon()
{
}

Daemon::Daemon(const Daemon& other)
{
    this->Init(other);
}

Daemon::~Daemon()
{
    this->Clear();
}

Daemon& Daemon::operator=(const Daemon& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Daemon::Init(const Daemon& other)
{
    /// @todo impl
}

void Daemon::Clear()
{
    /// @todo impl
}

void Daemon::Dump()
{
    /// @todo impl
}

}}
