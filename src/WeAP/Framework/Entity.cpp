
#include "Entity.h"



namespace WeAP { namespace Framework {



Entity::Entity()
{
}

Entity::Entity(const Entity& other)
{
    this->Init(other);
}

Entity::~Entity()
{
    this->Clear();
}

Entity& Entity::operator=(const Entity& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Entity::Init(const Entity& other)
{
    /// @todo impl
}

void Entity::Clear()
{
    /// @todo impl
}

void Entity::Dump()
{
    /// @todo impl
}

}}
