
#ifndef __WeAP_SQL_H__
#define __WeAP_SQL_H__


#include <string>
#include <sstream>
#include <iostream>
#include <stdint.h>
#include "Object.h"

using namespace std;
using namespace WeAP::System;

namespace WeAP { namespace MySQL {

class SQL: public Object
{
public:
    SQL();
    virtual ~SQL();

    SQL& Append(const string& str);

    SQL& AppendValue(int32_t value, bool end = false);
    SQL& AppendValue(uint32_t value, bool end = false);
    SQL& AppendValue(int64_t value, bool end = false);
    SQL& AppendValue(uint64_t value, bool end = false);
    SQL& AppendValue(const string& value, bool end = false);

    SQL& AppendValue(const string& name, int32_t value, bool end = false);
    SQL& AppendValue(const string& name, uint32_t value, bool end = false);
    SQL& AppendValue(const string& name, int64_t value, bool end = false);
    SQL& AppendValue(const string& name, uint64_t value, bool end = false);
    SQL& AppendValue(const string& name, const string& value, bool end = false);

    SQL& AppendCond(const string& name, int32_t value, bool end = false);
    SQL& AppendCond(const string& name, uint32_t value, bool end = false);
    SQL& AppendCond(const string& name, int64_t value, bool end = false);
    SQL& AppendCond(const string& name, uint64_t value, bool end = false);
    SQL& AppendCond(const string& name, const string& value, bool end = false);

    SQL& AppendExp(const string& name, const string& op, int32_t value, bool end = false);
    SQL& AppendExp(const string& name, const string& op, uint32_t value, bool end = false);
    SQL& AppendExp(const string& name, const string& op, int64_t value, bool end = false);
    SQL& AppendExp(const string& name, const string& op, uint64_t value, bool end = false);
    SQL& AppendExp(const string& name, const string& op, const string& value, bool end = false);

    string ToString();

protected:
    static string EscapeString(const string & str);

protected:
    stringstream sql;

};


}}

#endif

