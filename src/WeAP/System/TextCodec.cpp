#include "TextCodec.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include "Convert.h"
#include <assert.h>
#include "Error.h"
#include "Exception.h"

namespace WeAP { namespace System {


string TextCodec::UrlEncode(const string& str)
{
    std::string strTemp = "";
    size_t length = str.size();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) || 
            strchr("-_.!~*()\'", str[i]) != NULL)
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
            strTemp += Convert::CharToHex((unsigned char)str[i] >> 4);
            strTemp += Convert::CharToHex((unsigned char)str[i] % 16);
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
            if (i + 2 < length)
            {
                throw Exception(Error::TextCodec_UrlDecode_Failed, "UrlDecode failed");
            }

            unsigned char high = Convert::HexToChar((unsigned char)str[++i]);
            unsigned char low = Convert::HexToChar((unsigned char)str[++i]);
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