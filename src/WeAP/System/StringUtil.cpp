#include "StringUtil.h"
#include "Convert.h"

namespace WeAP { namespace System {

void StringUtil::Split(const string& str, char sep, vector<string>& strs)
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
        pos = str.find_first_of(sep, index);
        if(string::npos != pos)
        {
            if(pos > 0)
            {
                strs.push_back(str.substr(index, pos - index));
            }
            index = pos + 1;
        }
        else
        {
            strs.push_back(str.substr(index));
            break;
        }
    }while(index < len);

}

void StringUtil::Split(const string& str, char sep, vector<uint32_t>& list)
{
    vector<string> strs;
    StringUtil::Split(str, sep, strs);
    for (vector<string>::const_iterator it = strs.begin(); it != strs.end(); ++it)
    {
        list.push_back(Convert::ToUInt32(*it));
    }
}


void StringUtil::Split(const string& str, char sep, set<uint64_t>& list)
{
    set<string> strs;
    StringUtil::Split(str, sep, strs);
    for (set<string>::const_iterator it = strs.begin(); it != strs.end(); ++it)
    {
        list.insert(Convert::ToUInt64(*it));
    }
    
}

void StringUtil::Split(const string& str, char sep, set<string>& strs)
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
        pos = str.find_first_of(sep, index);
        if(string::npos != pos)
        {
            if(pos > 0)
            {
                strs.insert(str.substr(index, pos - index));
            }
            index = pos + 1;
        }
        else
        {
            strs.insert(str.substr(index));
            break;
        }
    }while(index < len);

}

bool StringUtil::IsDigit(const string& str)
{
    const char *p = str.c_str();

    while(isspace(*p))  p++;

    if(*p == '-') p++;

    while(isdigit(*p))  p++;

    while(isspace(*p))  p++;

    return !(*p);
}

bool StringUtil::IsAlphaDigit(const string& str)
{
    const char* p = str.c_str();

    while(isspace(*p)) p++;

    while(isdigit(*p) || isalpha(*p)) p++;

    while(isspace(*p)) p++;

    return !(*p);
}



string StringUtil::ToLower(const string& str)
{
    if (str.empty())
    {
        return str;
    }
    
    string outstr;
    for(size_t i = 0; i < str.size(); ++i)
    {
        outstr += tolower(str[i]);
    }
    return outstr;

}


string StringUtil::ToUpper(const string& str)
{
    if (str.empty())
    {
        return str;
    }
    
    string outstr;
    for(size_t i = 0; i < str.size(); ++i)
    {
        outstr += toupper(str[i]);
    }
    return outstr;
}

bool StringUtil::Find(const string& str, const vector<string>& strList)
{
    const size_t size = strList.size();
    for(size_t i = 0; i < size; i++)
    {
        if (str == strList[i])
        {
            return true;
        }
    }
    return false;
}

bool StringUtil::Find(const string& str, const map<string,string>& strmap)
{
    map<string, string>::const_iterator it = strmap.find(str);
    if (it == strmap.end())
    {
        return false;
    }

    return true;    
}


string StringUtil::Right(const string& str, size_t size)
{
    size_t p = str.length();
    if (p < size)
    {
        p = 0;
    }
    else
    {
        p -= size;
    }

    return str.substr(p);
}

string StringUtil::Left(const string& str, size_t size)
{
    if (size >= str.length())
    {
        size = str.npos;
    }

    return str.substr(0, size);
}


string& StringUtil::Trim(string& str, const char* szTrimChar)
{
    StringUtil::LTrim(str, szTrimChar);
    StringUtil::RTrim(str, szTrimChar);
    return str;
}

string& StringUtil::LTrim(string& strSrc, const char* szTrimChar)
{
    if(szTrimChar == NULL)
        szTrimChar = "\x20\t\r\n";

    for(; !strSrc.empty() && strchr(szTrimChar, strSrc[0]) != NULL;)
    {
        strSrc.erase(strSrc.begin());
    }
    return strSrc;
}

string& StringUtil::RTrim(string& strSrc, const char* szTrimChar)
{
    if(szTrimChar == NULL)
        szTrimChar = "\x20\t\r\n";

    int pos = (int) strSrc.length() - 1;
    for(; pos >= 0 && strchr(szTrimChar, strSrc[pos]) != NULL; --pos)
    {
        strSrc.erase(pos);
    }
    return strSrc;
}


string StringUtil::Tail(const string& str, unsigned int n)
{
    if (str.size() <= n)
    {
        return str;
    }
    
    int pos = str.size() -n;
    return str.substr(pos);
    
}

string StringUtil::ReplaceSubStr(string rawStr, const string& from,const string& to)
{
    if (from == "")
    {
        return rawStr;
    }
    size_t pos = rawStr.find(from);
    string retstr;
    for (;pos != string::npos;)
    {
        retstr +=rawStr.substr(0,pos) + to;
        if (pos+from.length() < rawStr.length())
        {
            rawStr = rawStr.substr(pos+from.length(),rawStr.length()-pos-from.length());
        }
        else
        {
            rawStr="";
        }
        pos = rawStr.find(from);
    }
    retstr += rawStr;
    return retstr;
}

bool StringUtil::EqualIgnoreCase(const string& str1, const string& str2)
{
    if (StringUtil::ToUpper(str1) == StringUtil::ToUpper(str2))
    {
        return true;
    }

    return false;
    
}

}}