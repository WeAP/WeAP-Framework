#include "Logger.h"



namespace WeAP { namespace System {



Logger::Logger()
{
}

Logger::Logger(const Logger& other)
{
    this->Init(other);
}

Logger::~Logger()
{
    this->Clear();
}

Logger& Logger::operator=(const Logger& other)
{
    if(this == &other)
    {
        return *this;
    }

    this->Init(other);

    return *this;
}

void Logger::Init(const Logger& other)
{
    /// @todo impl
}

void Logger::Clear()
{
    /// @todo impl
}

void Logger::Dump()
{
    /// @todo impl
}

}}
