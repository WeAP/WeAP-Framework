#ifndef __WeAP_INIConfig_H__
#define __WeAP_INIConfig_H__

#include "AppObject.h"
#include "KVMap.h"
#include "ObjectMap.h"

using namespace WeAP::System;

namespace WeAP { namespace Framework {

class INIConfig: public WeAP::System::Object
//class INIConfig: public WeAP::Framework::AppObject
{
public:
    INIConfig();
    virtual ~INIConfig();

    void Init(const string& confFile);

    const KVMap& GetSection(const string& section) const;

    string GetString(const string& section, const string& key, const string& defalutValue) const;
    int32_t GetInt32(const string& section, const string& key, int32_t defalutValue) const;
    uint32_t GetUInt32(const string& section, const string& key, uint32_t defalutValue) const;
    int64_t GetInt64(const string& section, const string& key, int64_t defalutValue) const;
    uint64_t GetUInt64(const string& section, const string& key, uint64_t defalutValue) const;
    void GetList(const string& section, const string& key, char sep, vector<string>& list) const;
    void GetList(const string& section, const string& key, char sep, vector<uint32_t>& list) const;

private:
    INIConfig(const INIConfig& other);
    INIConfig& operator=(const INIConfig& other);

protected:
    string confFile;
    ObjectMap<KVMap> sections;

};

}}


#endif //__WeAP_INIConfig_H__

