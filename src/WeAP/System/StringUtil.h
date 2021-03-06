#ifndef __WeAP_StringUtil_H__
#define __WeAP_StringUtil_H__

#include "Object.h"

namespace WeAP { namespace System {


class StringUtil: public Object
{
private:
    StringUtil();

public:

    static void Split(const string& str, char sep, vector<string>& strs);
    static void Split(const string& str, char sep, vector<uint32_t>& list);

    static void Split(const string& str, char sep, set<uint64_t>& list);
    static void Split(const string& str, char sep, set<string>& strs);

    static bool IsNumeric(const string& str);
    static bool IsAlphanumeric(const string& str);

    static string ToLower(const string& str);
    static string ToUpper(const string& str);

    static bool Find(const string& str, const vector<string>& strList);
    static bool Find(const string& str, const map<string,string>& strmap);

    static string Right(const string& str, size_t size);
    static string Left(const string& str, size_t size);

    static string& Trim(string& str, const char* szTrimChar = NULL);
    static string& TrimLeft(string& strSrc, const char* szTrimChar = NULL);
    static string& TrimRight(string& strSrc, const char* szTrimChar = NULL);
    static string Tail(const string& str, unsigned int n); 

    static string ReplaceSubStr(string rawStr,const string& from, const string& to);

    static bool EqualIgnoreCase(const string& str1, const string& str2);

    static string Format(const char* format, ...);
};

}}

#endif //__WeAP_StringUtil_H__