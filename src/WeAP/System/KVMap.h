#ifndef __WeAP_KVMap_H__
#define __WeAP_KVMap_H__

#include "Object.h"

namespace WeAP { namespace System {

/**
 * 键值对map，封装对map<string, string>的操作
 * 
 * @author xzwang
 */
class KVMap: public Object
{
public:
    KVMap();
    virtual ~KVMap();

    void Parse(const string& str, char sep1 = '&', char sep2 = '=');

    KVMap& operator=(const KVMap &other);
    KVMap& operator=(const map<string, string> &other);
    bool operator==(const KVMap& other) const;
    string operator[](const string& key) const;

    int32_t GetInt32(const string& key, int32_t defaultValue = 0) const;
    uint32_t GetUInt32(const string& key, uint32_t defaultValue = 0) const;
    int64_t GetInt64(const string& key, int64_t defaultValue = 0) const;
    uint64_t GetUInt64(const string& key, uint64_t defaultValue = 0) const;
    string GetString(const string& key, const string& defaultValue = "") const;
    bool GetBool(const string& key, bool defaultValue = false) const;
    time_t GetTimestamp(const string& key, time_t defaultValue = 0);

    void Set(const string& key, int32_t value);
    void Set(const string& key, uint32_t value);
    void Set(const string& key, int64_t value);
    void Set(const string& key, uint64_t value);
    void Set(const string& key, const string& value);
    void Set(const string& key, const char* value);
    
    bool Find(const string& key) const;        
    bool IsNullOrEmpty(const string& key) const; 

    void Remove(const string& key);
    void Remove(const vector<string>& keys);

    bool IsEmpty() const;

    map<string, string>& GetMap();
    const map<string, string>& GetMap() const;

    string ToUrlString( char sep1 = '&', char sep2 = '=');

    void Clear();

protected:
    void SplitKeyValue(const string& kvstr, char sep, map<string, string>& resultMap);

public:
    map<string, string>  innerMap;

};


}}

#endif

