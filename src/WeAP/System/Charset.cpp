#include "Charset.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "Error.h"
#include "Exception.h"

namespace WeAP { namespace System {

bool Charset::IsUTF8(const string& str)
{
    Charset::IsUTF8(str.c_str(), str.size())
}


bool Charset::IsUTF8(const char* str, size_t size)   
{   
    bool isUTF8 = true;   
    unsigned char* start = (unsigned char*)str;   
    unsigned char* end = (unsigned char*)str + size;   
    while (start < end)   
    {   
        if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符   
        {   
            start++;   
        }   
        else if (*start < (0xC0)) // (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符   
        {   
            isUTF8 = false;   
            break;   
        }   
        else if (*start < (0xE0)) // (11100000): 此范围内为2字节UTF-8字符   
        {   
            if (start >= end - 1)    
                break;   
            if ((start[1] & (0xC0)) != 0x80)   
            {   
                isUTF8 = false;   
                break;   
            }   
            start += 2;   
        }    
        else if (*start < (0xF0)) // (11110000): 此范围内为3字节UTF-8字符   
        {   
            if (start >= end - 2)    
                break;   
            if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)   
            {   
                isUTF8 = false;   
                break;   
            }   
            start += 3;
        }    
        else  
        {   
            isUTF8 = false;   
            break;   
        }   
    }   
    return isUTF8;   
}  




}}