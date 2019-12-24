#include "SQL.h"

namespace WeAP { namespace MySQL {

Sql::Sql()
{

}
Sql::~Sql()
{

}

Sql& Sql::Append(const string& str)
{
    this->sql << str << " ";
    return *this;
}


Sql& Sql::AppendValue(int32_t value, bool end)
{
    this->sql << value;
    if (!end)
    {
        this->sql << value << ", ";
    }
    else
    {
        this->sql << value << " ";
    }
    
    return *this;
}
Sql& Sql::AppendValue(uint32_t value, bool end)
{
    this->sql << value;
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}
Sql& Sql::AppendValue(int64_t value, bool end)
{
    this->sql << value;
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}
Sql& Sql::AppendValue(uint64_t value, bool end)
{
    this->sql << value;
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}

Sql& Sql::AppendValue(const string& value, bool end)
{
    this->sql << "'" << Sql::EscapeString(value) << "'";
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}

Sql& Sql::AppendValue(const string& name, int32_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}
Sql& Sql::AppendValue(const string& name, uint32_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}
Sql& Sql::AppendValue(const string& name, int64_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}
Sql& Sql::AppendValue(const string& name, uint64_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}
Sql& Sql::AppendValue(const string& name, const string& value, bool end)
{
    this->sql << name << "='" << Sql::EscapeString(value) << "'";
    if (!end)
    {
        this->sql << ", ";
    }
    else
    {
        this->sql << " ";
    }
    return *this;
}

Sql& Sql::AppendCond(const string& name, int32_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}
Sql& Sql::AppendCond(const string& name, uint32_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}
Sql& Sql::AppendCond(const string& name, int64_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}
Sql& Sql::AppendCond(const string& name, uint64_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}
Sql& Sql::AppendCond(const string& name, const string& value, bool end)
{
    this->sql << name << "='" << Sql::EscapeString(value) << "'";
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}

Sql& Sql::AppendExp(const string& name, const string& op, int32_t value, bool end)
{
    this->sql << name << op << value;
}
Sql& Sql::AppendExp(const string& name, const string& op, uint32_t value, bool end)
{
    this->sql << name << op << value;
}
Sql& Sql::AppendExp(const string& name, const string& op, int64_t value, bool end)
{
    this->sql << name << op << value;
}
Sql& Sql::AppendExp(const string& name, const string& op, uint64_t value, bool end)
{
    this->sql << name << op << value;
}
Sql& Sql::AppendExp(const string& name, const string& op, const string& value, bool end)
{
    this->sql << name << op << "'" << value << "'";
}

string Sql::ToString()
{
    return this->sql.str();
}


string SQL::EscapeString(const string & str)
{
    int len = str.length();
    char tmp[len * 2 + 1] = {0};
    mysql_escape_string(tmp, str.c_str(), str.length());
    
    return string(tmp);
}


}}