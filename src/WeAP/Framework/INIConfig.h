#ifndef __WeAP_INIConfig_H__
#define __WeAP_INIConfig_H__

#include "AppObject.h"
#include "KVMap.h"
#include "ObjectMap.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class INIConfig : public AppObject
{

public:
    INIConfig();
    virtual ~INIConfig();

    void Init(const string& confFile);

    void GetSection(const string& section, KVMap& kvmap);

    string GetString(const string& section, const string& key, const string& defalutValue);
    int32_t GetInt32(const string& section, const string& key, int32_t defalutValue);
    uint32_t GetUInt32(const string& section, const string& key, uint32_t defalutValue);
    int64_t GetInt64(const string& section, const string& key, int64_t defalutValue);
    uint64_t GetUInt64(const string& section, const string& key, uint64_t defalutValue);
    void GetList(const string& section, const string& key, char sep, vector<string>& list);
    void GetList(const string& section, const string& key, char sep, vector<uint32_t>& list);

private:
    INIConfig(const INIConfig& other);
    INIConfig& operator=(const INIConfig& other);

protected:
    string confFile;
    ObjectMap<KVMap> sections;

};

}}


#endif //__WeAP_INIConfig_H__

