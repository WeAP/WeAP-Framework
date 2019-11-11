#ifndef __WeAP_Convert_H__
#define __WeAP_Convert_H__

#include "Object.h"


namespace WeAP { namespace System {


class Convert: public Object
{
private:
    Convert();
    
public:
    static string ToString(int32_t value);
    static string ToString(uint32_t value);
    static string ToString(int64_t value);
    static string ToString(uint64_t value);
    static string ToString(bool value);

    static int32_t ToInt32(const string& value, int32_t defaultValue = 0);
    static uint32_t ToUInt32(const string& value, uint32_t defaultValue = 0);
    static int64_t ToInt64(const string& value, int64_t defaultValue = 0);
    static uint64_t ToUInt64(const string& value, uint64_t defaultValue = 0);
    static bool ToBool(const string& value, bool defaultValue = false);

    static unsigned char CharToHex(unsigned char x);
    static unsigned char HexToChar(unsigned char x);

};

}}

#endif //__WeAP_Convert_H__