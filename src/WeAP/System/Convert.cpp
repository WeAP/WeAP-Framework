#include "Convert.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>


namespace WeAP { namespace System {

std::string Convert::ToString(int32_t value)
{
    char buffer [64] = {0};
    snprintf(buffer, sizeof(buffer), "%d", value);
    return std::string(buffer);
}

std::string Convert::ToString(uint32_t value)
{
    char buffer [64] = {0};
    snprintf(buffer, sizeof(buffer), "%u", value);
    return std::string(buffer);
}

std::string Convert::ToString(int64_t value)
{
    char buffer [64] = {0};
    snprintf(buffer, sizeof(buffer), "%" PRId64, value);
    return std::string(buffer);
}

std::string Convert::ToString(uint64_t value)
{
    char buffer [64] = {0};
    snprintf(buffer, sizeof(buffer), "%" PRIu64, value);
    return std::string(buffer);
}

std::string Convert::ToString(bool value)
{
    if (value == true)
    {
        return "1";
    }
    else
    {
        return "0";
    }
    
}

int32_t Convert::ToInt32(const string& value, int32_t defaultValue)
{
    if (value.empty())
    {
        return defaultValue;
    }

    int32_t ivalue;
    std::stringstream ss(value);
    ss >> ivalue;
    return ivalue;
}

uint32_t Convert::ToUInt32(const string& value, uint32_t defaultValue)
{
    if (value.empty())
    {
        return defaultValue;
    }

    uint32_t ivalue;
    std::stringstream ss(value);
    ss >> ivalue;
    return ivalue;
}


int64_t Convert::ToInt64(const string& value, int64_t defaultValue)
{
    if (value.empty())
    {
        return defaultValue;
    }

    return ::atoll(value.c_str());
}

uint64_t Convert::ToUInt64(const string& value, uint64_t defaultValue)
{
    if (value.empty())
    {
        return defaultValue;
    }

    return ::atoll(value.c_str());
}

bool Convert::ToBool(const string& value, bool defaultValue)
{
    if (value == "0")
    {
        return false;
    }
    else if (value == "1")
    {
        return true;
    }
    else
    {
        return defaultValue;
    }
    
}


}}