
#include "INIConfig.h"
#include "Util.h"
#include <sys/stat.h>
#include "FileUtil.h"

namespace WeAP { namespace Framework {


INIConfig::INIConfig()
{
}



INIConfig::~INIConfig()
{

}

void INIConfig::Init(const string& confFile)
{
    this->confFile = confFile;
    vector<string> lines;
    FileUtil::ReadLines(confFile, lines);
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (lines[i] == "[")
        {
            //@todo
        }
    }
}

void INIConfig::GetSection(const string& section, KVMap& kvmap)
{
    kvmap = *(this->setctions[section]);
}

string INIConfig::GetString(const string& section, const string& key)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetString(key);
}

int32_t INIConfig::GetInt32(const string& section, const string& key)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetInt32(key);
}

uint32_t INIConfig::GetUInt32(const string& section, const string& key)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetUInt32(key);
}

int64_t INIConfig::GetInt64(const string& section, const string& key)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetInt64(key);
}

uint64_t INIConfig::GetUInt64(const string& section, const string& key)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetUInt64(key);
}

void INIConfig::GetList(const string& section, const string& key, char sep, vector<string>& list)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetList(key, sep);
}

void INIConfig::GetList(const string& section, const string& key, char sep, vector<uint32_t>& list)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetList(key, sep);
}





}}
