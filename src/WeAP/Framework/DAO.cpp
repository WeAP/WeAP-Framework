
#include "DAO.h"



namespace WeAP { namespace Framework {



DAO::DAO()
{
}

DAO::DAO(const DAO& other)
{
    this->Init(other);
}

DAO::~DAO()
{
    this->Clear();
}

DAO& DAO::operator=(const DAO& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void DAO::Init(const DAO& other)
{
    /// @todo impl
}

void DAO::Clear()
{
    /// @todo impl
}

void DAO::Dump()
{
    /// @todo impl
}

}}
