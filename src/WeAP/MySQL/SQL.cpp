#include "SQL.h"
#include <string.h>
#include "mysql.h"

namespace WeAP { namespace MySQL {

SQL::SQL()
{

}
SQL::~SQL()
{

}

SQL& SQL::Append(const string& str)
{
    this->sql << str << " ";
    return *this;
}


SQL& SQL::AppendValue(int32_t value, bool end)
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
SQL& SQL::AppendValue(uint32_t value, bool end)
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
SQL& SQL::AppendValue(int64_t value, bool end)
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
SQL& SQL::AppendValue(uint64_t value, bool end)
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

SQL& SQL::AppendValue(const string& value, bool end)
{
    this->sql << "'" << SQL::EscapeString(value) << "'";
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

SQL& SQL::AppendValue(const string& name, int32_t value, bool end)
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
SQL& SQL::AppendValue(const string& name, uint32_t value, bool end)
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
SQL& SQL::AppendValue(const string& name, int64_t value, bool end)
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
SQL& SQL::AppendValue(const string& name, uint64_t value, bool end)
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
SQL& SQL::AppendValue(const string& name, const string& value, bool end)
{
    this->sql << name << "='" << SQL::EscapeString(value) << "'";
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

SQL& SQL::AppendCond(const string& name, int32_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}
SQL& SQL::AppendCond(const string& name, uint32_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}
SQL& SQL::AppendCond(const string& name, int64_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}
SQL& SQL::AppendCond(const string& name, uint64_t value, bool end)
{
    this->sql << name << "=" << value;
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}
SQL& SQL::AppendCond(const string& name, const string& value, bool end)
{
    this->sql << name << "='" << SQL::EscapeString(value) << "'";
    if (!end)
    {
        this->sql << " and ";
    }
    return *this;
}

SQL& SQL::AppendExp(const string& name, const string& op, int32_t value, bool end)
{
    this->sql << name << op << value;
    return *this;
}
SQL& SQL::AppendExp(const string& name, const string& op, uint32_t value, bool end)
{
    this->sql << name << op << value;
    return *this;
}
SQL& SQL::AppendExp(const string& name, const string& op, int64_t value, bool end)
{
    this->sql << name << op << value;
    return *this;
}
SQL& SQL::AppendExp(const string& name, const string& op, uint64_t value, bool end)
{
    this->sql << name << op << value;
    return *this;
}
SQL& SQL::AppendExp(const string& name, const string& op, const string& value, bool end)
{
    this->sql << name << op << "'" << value << "'";
    return *this;
}

string SQL::ToString()
{
    return this->sql.str();
}


string SQL::EscapeString(const string & str)
{
    int len = str.length();
    char tmp[len * 2 + 1];
    memset(tmp, 0, sizeof(tmp));
    mysql_escape_string(tmp, str.c_str(), len);
    
    return string(tmp);
}


}}