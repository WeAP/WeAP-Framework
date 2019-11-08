
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

    KVMap* currMap;
    for (size_t i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        if (line[0] == '[')
        {
            size_t right = line.find(']');
            string section = line.substr(1, right);
            currMap = this->sections.Add(section);
        }
        else 
        {
            size_t pos = kvstr.find('=');
            if(pos != std::string::npos)
            {
                string key = kvstr.substr(0, pos);
                string value = kvstr.substr(pos + 1);     
                currMap->Set(key, value);
            }
            else
            {
                throw Exception(Error::INIConfig_Formate_Error, "lack of =");
            }
            
        }
        
    }
}


void INIConfig::GetSection(const string& section, KVMap& kvmap)
{
    kvmap = *(this->setctions[section]);
}

string INIConfig::GetString(const string& section, const string& key, const string& defalutValue)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetString(key, defalutValue);
}

int32_t INIConfig::GetInt32(const string& section, const string& key, int32_t defalutValue)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetInt32(key, defalutValue);
}

uint32_t INIConfig::GetUInt32(const string& section, const string& key, uint32_t defalutValue)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetUInt32(key, defalutValue);
}

int64_t INIConfig::GetInt64(const string& section, const string& key, int64_t defalutValue)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetInt64(key, defalutValue);
}

uint64_t INIConfig::GetUInt64(const string& section, const string& key, uint64_t defalutValue)
{
    KVMap kvmap;
    this->GetSection(section, kvmap);
    return kvmap.GetUInt64(key, defalutValue);
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
