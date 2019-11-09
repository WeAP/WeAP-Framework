#include "TextCodec.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>


namespace WeAP { namespace System {


string TextCodec::UrlEncode(const string& str)
{
    std::string strTemp = "";
    size_t length = str.size();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) || 
            (str[i] == '-') ||
            (str[i] == '_') || 
            (str[i] == '.') || 
            (str[i] == '~'))
        {
            strTemp += str[i];
        }
        else if (str[i] == ' ')
        {
            strTemp += "+";
        }
        else
        {
            strTemp += '%';
            strTemp += Convert::ToHex((unsigned char)str[i] >> 4);
            strTemp += Convert::ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

string TextCodec::UrlDecode(const string& str)
{
    std::string strTemp = "";
    size_t length = str.size();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+') 
        {
            strTemp += ' ';
        }
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = Convert::FromHex((unsigned char)str[++i]);
            unsigned char low = Convert::FromHex((unsigned char)str[++i]);
            strTemp += high*16 + low;
        }
        else 
        {
            strTemp += str[i];
        }
    }
    return strTemp;
}




}}