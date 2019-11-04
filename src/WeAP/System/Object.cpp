#include "Object.h"



namespace WeAP{ namespace System {



Object::Object()
{
}

Object::Object(const Object& other)
{
    this->Init(other);
}

Object::~Object()
{

}

Object& Object::operator=(const Object& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Object::Dump()
{

}

void Object::Init(const Object& other)
{
    // do nothing
}


}}
