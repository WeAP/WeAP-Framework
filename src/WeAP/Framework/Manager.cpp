
#include "Manager.h"



namespace WeAP { namespace Framework {



Manager::Manager()
{
}

Manager::Manager(const Manager& other)
{
    this->Init(other);
}

Manager::~Manager()
{
    this->Clear();
}

Manager& Manager::operator=(const Manager& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Manager::Init(const Manager& other)
{
    /// @todo impl
}

void Manager::Clear()
{
    /// @todo impl
}

void Manager::Dump()
{
    /// @todo impl
}

}}
