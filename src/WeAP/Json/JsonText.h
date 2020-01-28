#ifndef __WeAP_JsonText_H__
#define __WeAP_JsonText_H__


#include "json/json.h"
#include "Object.h"


using namespace std;
using namespace WeAP::System;

namespace WeAP { namespace Json {

/**
 * 
 */
class JsonText: public Object
{
public:
    JsonText();
    virtual ~JsonText();
    
    int Parse(const string& jsonString);

    int Load(const string& jsonFilePath);

    std::string operator[](const string& nodeName) const;

    std::string GetString(const string& nodeName, const string& defaultValue = "") const;
    int GetInt(const string& nodeName, int defaultValue = 0) const;
    uint32_t GetUInt32(const string& nodeName, uint32_t defaultValue = 0) const;
    double GetDouble(const string& nodeName, double defaultValue = 0) const;
    string GetDouble2String(const string& nodeName, const string& defaultValue = "") const;

    std::string GetString(const string& nodeName) const;
    int GetInt(const string& nodeName) const;
    uint32_t GetUInt32(const string& nodeName) const;
    double GetDouble(const string& nodeName) const;
    string GetDouble2String(const string& nodeName) const;
    void GetObject(const string& nodeName, JsonText& jsonObject) const;

    void SetValue(const string& name, const char* value);
    void SetValue(const string& name, const string& value);
    void SetValue(const string& name, int value);
    void SetValue(const string& name, const JsonText& value);

    bool IsNullOrEmpty(const string& nodeName) const;
    bool IsNull(const string& nodeName) const;

    void GetArray(size_t index, const string &arrayName, JsonText& jsonText) const;
    int GetArrayCount(const string &arrayName) const;
    void AppendArray(const JsonText& item);

    std::string ToString() const;
 
    string ToStyledString() const;

    string ToEscapeString() const;

    void AssertNullOrEmpty(const string& nodeName);
    void AssertNull(const string& nodeName);

public:
    Json::Value* jsonValue;
};



}}


#endif
