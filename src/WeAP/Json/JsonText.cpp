#include "JsonText.h"
#include <sstream>
#include "Logger.h"

namespace WeAP { namespace Json {

JsonText::JsonText()
{
    this->jsonValue = new Json::Value();
}

JsonText::~JsonText()
{
    if (this->jsonValue != NULL)
    {
        delete this->jsonValue;
        this->jsonValue = NULL;
    }
}

int JsonText::Parse(const string &jsonString)
{ 
    Json::Reader reader;
    bool succ = reader.parse(jsonString, (*(this->jsonValue)));
    if (!succ)
    {
        int iErr = -1;
        ERROR("Json::Reader.parse, jsonstr:%s", jsonString.c_str());
        return iErr;
    }
    return 0;
}

int JsonText::Load(const string& jsonFilePath)
{ 
    //从文件中读取
    ifstream jsonFile(jsonFilePath, ios::binary);
 
    if(!jsonFile.is_open())  
    { 
        int iErr = -1;
        ERROR("ifstream.is_open, jsonFilePath:%s", jsonFilePath.c_str());
        return iErr; 
    }

    Json::Reader reader;
    bool succ = reader.parse(jsonFile, *(this->jsonValue));
    if(!succ)
    {
        int iErr = -2;
        ERROR("Json::Reader.parse, jsonFilePath:%s", jsonFilePath.c_str());
        return iErr;
    }

    return 0;
}


std::string JsonText::operator[](const string& nodeName) const
{
    return this->GetString(nodeName);
}

string JsonText::GetString(const string &nodeName, const string& defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        //WARNING("IsNull", -2, "json node is not member or null, nodeName:%s", nodeName.c_str());        
        return defaultValue;        
    }

    if (!(*(this->jsonValue))[nodeName].isString())
    {
        //WARNING("jsoncpp.isString", -4, "json node is not string, nodeName:%s", nodeName.c_str());        
        return defaultValue;
    }

    return (*(this->jsonValue))[nodeName].asString();
}

int JsonText::GetInt(const string& nodeName, int defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        //WARNING("IsNull", -2, "json node is not member or null, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;        
    }


    if (!(*(this->jsonValue))[nodeName].isInt())
    {
        //WARNING("jsoncpp.isInt", -4, "json node is not int, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }
    return (*(this->jsonValue))[nodeName].asInt();
}

uint32_t JsonText::GetUInt32(const string& nodeName, uint32_t defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        //WARNING("IsNull", -2, "json node is not member or null, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;        
    }

    if (!(*(this->jsonValue))[nodeName].isUInt())
    {
        //WARNING("jsoncpp.isInt", -4, "json node is not uint, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }
    return (*(this->jsonValue))[nodeName].asUInt();
}

double JsonText::GetDouble(const string& nodeName, double defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        //WARNING("IsNull", -2, "json node is not member or null, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }

    if (!(*(this->jsonValue))[nodeName].isDouble())
    {
        //WARNING("jsoncpp.isDouble", -4, "json node is not int, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }
    return (*(this->jsonValue))[nodeName].asDouble();
}


string JsonText::GetDouble2String(const string& nodeName, const string& defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        //WARNING("IsNull", -2, "json node is not member or null, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }

    if (!(*(this->jsonValue))[nodeName].isDouble())
    {
        //WARNING("jsoncpp.isDouble", -4, "json node is not int, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }
    return std::to_string((*(this->jsonValue))[nodeName].asDouble());
}



void JsonText::GetObject(const string& nodeName, JsonText& jsonObject) const
{
    if (this->IsNull(nodeName))
    {
        //WARNING("IsNull, json node is not member or null, nodeName:%s", nodeName.c_str());
        return ;
    }

    if (!(*(this->jsonValue))[nodeName].isObject())
    {
        //WARNING("jsoncpp.isObject, json node is not object, nodeName:%s", nodeName.c_str());
        return ;
    }

    *(jsonObject.jsonValue) = (*(this->jsonValue))[nodeName];
}


void JsonText::SetValue(const string& name, const char* value)
{
    (*(this->jsonValue))[name] = value;
}

void JsonText::SetValue(const string& name, const string& value)
{
    (*(this->jsonValue))[name] = value;
}

void JsonText::SetValue(const string& name, int value)
{
    std::stringstream strsteam;
    strsteam << value;
    (*(this->jsonValue))[name] = strsteam.str();
}

void JsonText::SetValue(const string& name, const JsonText& value)
{
    (*(this->jsonValue))[name] = value.jsonValue;
}

void JsonText::GetArray(size_t index, const string &arrayName, JsonText& jsonText) const
{
    if (this->IsNull(arrayName))
    {
        WARNING("IsNull", -2, "json node is not member or null, arrayName:%s", arrayName.c_str());
        return;
    }

    if (!(*(this->jsonValue))[arrayName].isArray())
    {
        WARNING("jsoncpp.isArray", -3, "json node is not array, arrayName:%s", arrayName.c_str());
        return;
    }

    if (!(*(this->jsonValue))[arrayName].isValidIndex(index))
    {
        WARNING("jsoncpp.isValidIndex", -4, "json array index is not valid, arrayName:%s", arrayName.c_str());
        return;
    }

    *(jsonText.jsonValue) = (*(this->jsonValue))[arrayName][(int)index];
}

int JsonText::GetArrayCount(const string &arrayName) const
{
    if (this->IsNull(arrayName))
    {
        return 0;
    }
    return (*(this->jsonValue))[arrayName].size();
}

bool JsonText::IsNullOrEmpty(const string& nodeName) const
{
    if (this->IsNull(nodeName))
    {
        return true;
    }

    if (!(*(this->jsonValue))[nodeName].isString())
    {
       return true;
    }

    if ((*(this->jsonValue))[nodeName].asString().empty())
    {
        return true;
    }

    return false;
}

bool JsonText::IsNull(const string& nodeName) const
{
    if (!this->jsonValue->isMember(nodeName))
    {
        return true;
    }

    if ((*(this->jsonValue))[nodeName].isNull())
    {
        return true;
    }

    return false;

}



void JsonText::AppendArray(const JsonText& item)
{
    this->jsonValue->append(item.jsonValue);
}

string JsonText::ToString() const
{
    Json::FastWriter jsonWriter;
    string str = jsonWriter.write(*(this->jsonValue));    

    //去除末尾换行符
    if ((str.length() >= 1) && (str.at(str.length() - 1) == '\n'))
    {
        str = str.substr(0, str.length() - 1);
    }

    return str;
    
}


string JsonText::ToStyledString() const
{
    Json::StyledWriter sw;
    return sw.write(*(this->jsonValue));
}

string JsonText::ToEscapeString() const
{
    string outstr;
    string str = this->ToString();
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '"')
        {
            outstr += "\\";
            outstr += str[i];
        }
        else
        {
            outstr += str[i];
        }
    }
    
    return outstr;
}


void JsonText::AssertNullOrEmpty(const string& nodeName)
{
    if (this->IsNullOrEmpty(nodeName))
    {
        //WARNING("node is null, nodeName=%s", nodeName.c_str());
    } 
}

void JsonText::AssertNull(const string& nodeName)
{
    if (this->IsNull(nodeName))
    {
        //WARNING("node is null, nodeName=%s", nodeName.c_str());
    } 
}


}}


