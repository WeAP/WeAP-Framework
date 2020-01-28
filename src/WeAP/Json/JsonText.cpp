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
        ERROR("Json::Reader.parse, jsonstr:%s", jsonString.c_str());
        throw Exception(Error::JsonText_Parse_Failed, "json reader parsed failed");
    }
    return 0;
}

int JsonText::Load(const string& jsonFilePath)
{ 
    //从文件中读取
    ifstream jsonFile(jsonFilePath, ios::binary);
 
    if(!jsonFile.is_open())  
    {
        ERROR("ifstream.is_open, jsonFilePath:%s", jsonFilePath.c_str());
        throw Exception(Error::JsonText_Open_File_Failed, "open json file failed.");
    }

    Json::Reader reader;
    bool succ = reader.parse(jsonFile, *(this->jsonValue));
    if(!succ)
    {
        int iErr = -2;
        ERROR("Json::Reader.parse, jsonFilePath:%s", jsonFilePath.c_str());
        throw Exception(Error::JsonText_Parse_Failed, "json reader parsed failed");
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
        WARNING("json node is not member or null, nodeName:%s", nodeName.c_str());        
        return defaultValue;        
    }

    if (!(*(this->jsonValue))[nodeName].isString())
    {
        WARNING("json node is not string, nodeName:%s", nodeName.c_str());        
        return defaultValue;
    }

    return (*(this->jsonValue))[nodeName].asString();
}

int JsonText::GetInt(const string& nodeName, int defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        WARNING("json node is not member or null, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;        
    }


    if (!(*(this->jsonValue))[nodeName].isInt())
    {
        WARNING("json node is not int, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }
    return (*(this->jsonValue))[nodeName].asInt();
}

uint32_t JsonText::GetUInt32(const string& nodeName, uint32_t defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        WARNING("json node is not member or null, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;        
    }

    if (!(*(this->jsonValue))[nodeName].isUInt())
    {
        WARNING("json node is not uint, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }
    return (*(this->jsonValue))[nodeName].asUInt();
}

double JsonText::GetDouble(const string& nodeName, double defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        WARNING("json node is not member or null, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }

    if (!(*(this->jsonValue))[nodeName].isDouble())
    {
        WARNING("json node is not int, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }
    return (*(this->jsonValue))[nodeName].asDouble();
}


string JsonText::GetDouble2String(const string& nodeName, const string& defaultValue) const
{
    if (this->IsNull(nodeName))
    {
        /ARNING("json node is not member or null, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }

    if (!(*(this->jsonValue))[nodeName].isDouble())
    {
        WARNING("json node is not int, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        return defaultValue;
    }
    return std::to_string((*(this->jsonValue))[nodeName].asDouble());
}


string JsonText::GetString(const string &nodeName) const
{
    this->AssertNull(nodeName);

    if (!(*(this->jsonValue))[nodeName].isString())
    {
        ERROR("json node is not string, nodeName:%s", nodeName.c_str());        
        throw Exception(Error::JsonText_Node_Is_Not_String, "json node is not string");
    }

    return (*(this->jsonValue))[nodeName].asString();
}

int JsonText::GetInt(const string& nodeName, int defaultValue) const
{
    this->AssertNull(nodeName);

    if (!(*(this->jsonValue))[nodeName].isInt())
    {
        ERROR("json node is not int, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        throw Exception(Error::JsonText_Node_Is_Not_Int, "json node is not int");
    }
    return (*(this->jsonValue))[nodeName].asInt();
}

uint32_t JsonText::GetUInt32(const string& nodeName, uint32_t defaultValue) const
{
    this->AssertNull(nodeName);

    if (!(*(this->jsonValue))[nodeName].isUInt())
    {
        ERROR("json node is not uint, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        throw Exception(Error::JsonText_Node_Is_UInt, "json node is not uint");
    }
    return (*(this->jsonValue))[nodeName].asUInt();
}

double JsonText::GetDouble(const string& nodeName, double defaultValue) const
{
    this->AssertNull(nodeName);

    if (!(*(this->jsonValue))[nodeName].isDouble())
    {
        ERROR("json node is not double, nodeName:%s, json_str:%s", nodeName.c_str(), this->ToString().c_str());
        throw Exception(Error::JsonText_Node_Is_Double, "json node is not double");
    }
    return (*(this->jsonValue))[nodeName].asDouble();
}


string JsonText::GetDouble2String(const string& nodeName) const
{
    double val = this->GetDouble(nodeName);
    return std::to_string(val);
}


void JsonText::GetObject(const string& nodeName, JsonText& jsonObject) const
{
    this->AssertNull(nodeName);

    if (!(*(this->jsonValue))[nodeName].isObject())
    {
        ERROR("json node is not object, nodeName:%s", nodeName.c_str());
        throw Exception(Error::JsonText_Node_Is_Object, "json node is not object");
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
    this->AssertNull(arrayName);

    if (!(*(this->jsonValue))[arrayName].isArray())
    {
        ERROR("json node is not array, arrayName:%s", arrayName.c_str());
        throw Exception(Error::JsonText_Node_Is_Not_Array, "json node is not array");
    }

    if (!(*(this->jsonValue))[arrayName].isValidIndex(index))
    {
        WARNING("json array index is not valid, arrayName:%s", arrayName.c_str());
        
        throw Exception(Error::JsonText_Array_Index_Is_Not_Valid, "json array index is not valid");
    }

    *(jsonText.jsonValue) = (*(this->jsonValue))[arrayName][(int)index];
}

int JsonText::GetArrayCount(const string &arrayName) const
{
    this->AssertNull(arrayName);
    
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
        ERROR("json node is not member or null, nodeName:%s", nodeName.c_str());
        throw Exception(Error::JsonText_Node_Is_Empty_Or_NULL, "json node is not member or null");
    } 
}

void JsonText::AssertNull(const string& nodeName)
{
    if (this->IsNull(nodeName))
    {
        ERROR("json node is not member or null, nodeName:%s", nodeName.c_str());
        throw Exception(Error::JsonText_Node_Is_NULL, "json node is not member or null");
    } 
}


}}


