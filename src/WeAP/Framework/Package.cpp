
#include "Package.h"



namespace WeAP { namespace Framework {



Package::Package()
{
}

Package::Package(const Package& other)
{
    this->Init(other);
}

Package::~Package()
{
    this->Clear();
}

Package& Package::operator=(const Package& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Package::Init(const Package& other)
{
    /// @todo impl
}

void Package::Clear()
{
    /// @todo impl
}

void Package::Dump()
{
    /// @todo impl
}

}}
