
#ifndef __WeAP_SQL_H__
#define __WeAP_SQL_H__


#include <string>
#include <sstream>
#include <iostream>


using namespace std;

namespace WeAP { namespace MySQL {

class Sql
{
public:
    Sql();
    virtual ~Sql();

    Sql& Append(const string& str);

    Sql& AppendValue(int32_t value, bool end = false);
    Sql& AppendValue(uint32_t value, bool end = false);
    Sql& AppendValue(int64_t value, bool end = false);
    Sql& AppendValue(uint64_t value, bool end = false);
    Sql& AppendValue(const string& value, bool end = false);

    Sql& AppendValue(const string& name, int32_t value, bool end = false);
    Sql& AppendValue(const string& name, uint32_t value, bool end = false);
    Sql& AppendValue(const string& name, int64_t value, bool end = false);
    Sql& AppendValue(const string& name, uint64_t value, bool end = false);
    Sql& AppendValue(const string& name, const string& value, bool end = false);

    Sql& AppendCond(const string& name, int32_t value, bool end = false);
    Sql& AppendCond(const string& name, uint32_t value, bool end = false);
    Sql& AppendCond(const string& name, int64_t value, bool end = false);
    Sql& AppendCond(const string& name, uint64_t value, bool end = false);
    Sql& AppendCond(const string& name, const string& value, bool end = false);

    Sql& AppendExp(const string& name, const string& op, int32_t value, bool end = false);
    Sql& AppendExp(const string& name, const string& op, uint32_t value, bool end = false);
    Sql& AppendExp(const string& name, const string& op, int64_t value, bool end = false);
    Sql& AppendExp(const string& name, const string& op, uint64_t value, bool end = false);
    Sql& AppendExp(const string& name, const string& op, const string& value, bool end = false);

    string ToString();

protected:
    static string EscapeString(const string & str);

protected:
    stringstream sql;

};


}}

#endif

