#include "KVMap.h"
#include "Convert.h"
#include "DateTime.h"
#include "TextCodec.h"
#include "StringUtil.h"

namespace WeAP { namespace System {


KVMap::KVMap()
{
}

KVMap::~KVMap()
{
    this->Clear();
}

void KVMap::Parse(const string& str, char sep1, char sep2)
{
    if (str.empty())
    {
        return;
    }
    
    unsigned index = 0;
    string::size_type pos = 0;
    size_t len = str.size();

    do
    {
        pos = str.find_first_of(sep1, index);
        if(string::npos != pos)
        {
            if(pos > 0)
            {
                string kvstr = str.substr(index, pos - index);
                this->SplitKeyValue(kvstr, sep2, this->innerMap);
            }
            index = pos + 1;
        }
        else
        {
            string kvstr = str.substr(index);
            this->SplitKeyValue(kvstr, sep2, this->innerMap);
            break;
        }
    }
    while(index < len);
}

void KVMap::SplitKeyValue(const string& kvstr, char sep, map<string, string>& resultMap)
{
    if(kvstr.empty())
    {
        return ;
    }
    string::size_type pos = kvstr.find(sep);
    if(pos != std::string::npos)
    {
        string key = kvstr.substr(0, pos);
        string value = kvstr.substr(pos + 1);     

        resultMap[key] = TextCodec::UrlDecode(value); 
    }
}

KVMap& KVMap::operator=(const KVMap &other) 
{
    if(this == &other)
    {
        return *this;
    }
    
    this->innerMap = other.innerMap;

    return *this;
};

KVMap& KVMap::operator=(const map<string, string> &other) 
{    
    this->innerMap = other;
 
    return *this;
};

bool KVMap::operator==(const KVMap& other) const
{
    if(this == &other)
    {
        return true;
    }
    
    if (this->innerMap != other.innerMap) 
    {
        return false;
    }

    return true;
}

string KVMap::operator[](const string& key) const
{
    return this->GetString(key, "");
}

int32_t KVMap::GetInt32(const string& key, int32_t defaultValue) const
{
    map<string, string>::const_iterator it = this->innerMap.find(key);
    if (it == this->innerMap.end() || it->second.empty())
    {
        return defaultValue;
    }

    return Convert::ToInt32(it->second, defaultValue);
}

uint32_t KVMap::GetUInt32(const string& key, uint32_t defaultValue) const
{
    map<string, string>::const_iterator it = this->innerMap.find(key);
    if (it == this->innerMap.end() || it->second.empty())
    {
        return defaultValue;
    }

    return Convert::ToUInt32(it->second, defaultValue);
}

int64_t KVMap::GetInt64(const string& key, int64_t defaultValue) const
{
    map<string, string>::const_iterator it = this->innerMap.find(key);
    if (it == this->innerMap.end() || it->second.empty())
    {
        return defaultValue;
    }

    return Convert::ToInt64(it->second, defaultValue);
}


uint64_t KVMap::GetUInt64(const string& key, uint64_t defaultValue) const
{
    map<string, string>::const_iterator it = this->innerMap.find(key);
    if (it == this->innerMap.end() || it->second.empty())
    {
        return defaultValue;
    }

    return Convert::ToUInt64(it->second, defaultValue);
}


string KVMap::GetString(const string& key, const string& defaultValue) const
{
    map<string, string>::const_iterator it = this->innerMap.find(key);
    if (it == this->innerMap.end())
    {
        return defaultValue;
    }

    return it->second;

}   

bool KVMap::GetBool(const string& key, bool defaultValue) const
{
    map<string, string>::const_iterator it = this->innerMap.find(key);
    if (it == this->innerMap.end() || it->second.empty())
    {
        return defaultValue;
    }

    if (it->second == "1")
    {
        return true;
    }
    else if (it->second == "0")
    {
        return false;
    }
    else
    {
        return true;
    }
    
}   

time_t KVMap::GetTimestamp(const string& key, time_t defaultValue) const
{
    string dt = this->GetString(key);
    return DateTime(dt).GetTimestamp();
}

void KVMap::GetList(const string& key, char sep, vector<string>& list) const
{
    string value = this->GetString(key);
    StringUtil::Split(value, sep, list);
}

void KVMap::GetList(const string& key, char sep, vector<uint32_t>& list) const
{
    string value = this->GetString(key);
    StringUtil::Split(value, sep, list);
}


void KVMap::Set(const string& key, int32_t value)
{
    this->innerMap[key] = Convert::ToString(value);
}

void KVMap::Set(const string& key, uint32_t value)
{
    this->innerMap[key] = Convert::ToString(value);
}

void KVMap::Set(const string& key, int64_t value)
{
    this->innerMap[key] = Convert::ToString(value);
}

void KVMap::Set(const string& key, uint64_t value)
{
    this->innerMap[key] = Convert::ToString(value);
}

void KVMap::Set(const string& key, const string& value)
{
    this->innerMap[key] = value;
}

void KVMap::Set(const string& key, const char* value)
{
    this->innerMap[key] = value; 
}


bool KVMap::Find(const string& key) const
{
    map<string, string>::const_iterator iter = this->innerMap.find(key);
    if (iter != this->innerMap.end())
    {
        return true;
    }

    return false;
}

bool KVMap::Exist(const string& key) const
{
    map<string, string>::const_iterator iter = this->innerMap.find(key);
    if (iter != this->innerMap.end())
    {
        return true;
    }

    return false;
}

bool KVMap::IsNullOrEmpty(const string& key) const
{
    if (!this->Find(key))
    {
        return true;
    }
    if ("" == this->innerMap.at(key))
    {
        return true;
    }

    return false;
}

void KVMap::Remove(const string& key)
{
    this->innerMap.erase(key);
}

void KVMap::Remove(const vector<string>& keys)
{
    const size_t size = keys.size();
    for (size_t i = 0; i < size; ++i)
    {
        this->innerMap.erase(keys[i]);
    }
}

bool KVMap::IsEmpty() const
{
    if (this->innerMap.empty())
    {
        return true;
    }

    return false;
}


map<string, string>& KVMap::GetMap()
{
    return this->innerMap;
}

const map<string, string>& KVMap::GetMap() const
{
    return this->innerMap;
}

void KVMap::Clear()
{
    this->innerMap.clear();
}

string KVMap::ToUrlString(char sep1, char sep2) const
{
    string str;

    size_t len = this->innerMap.size();
    size_t i = 0;

    for (map<string, string>::const_iterator it = this->innerMap.begin(); it != this->innerMap.end(); ++it)
    {        
        i++;
        if (i != len)
        {
            str += it->first;
            str += sep2;
            str += TextCodec::UrlEncode(it->second);
            str += sep1;
        }
        else
        {
            str += it->first;
            str += sep2;
            str += TextCodec::UrlEncode(it->second);
        }
    } 

    return str;
}

string KVMap::ToString(char sep1, char sep2) const
{
    string str;

    size_t len = this->innerMap.size();
    size_t i = 0;

    for (map<string, string>::const_iterator it = this->innerMap.begin(); it != this->innerMap.end(); ++it)
    {        
        i++;
        if (i != len)
        {
            str += it->first;
            str += sep2;
            str += it->second;
            str += sep1;
        }
        else
        {
            str += it->first;
            str += sep2;
            str += it->second;
        }
    } 

    return str;
}

}}

