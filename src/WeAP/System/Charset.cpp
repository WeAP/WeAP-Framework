#include "Charset.h"
#include "Error.h"
#include "Exception.h"
#include <iconv.h>

namespace WeAP { namespace System {

string Charset::GBKToUTF8(const string& str)
{
    return Charset::Convert(str, Charset::GBK, Charset::UTF8);
};


string Charset::UTF8ToGBK(const string& str)
{
    return Charset::Convert(str, Charset::UTF8, Charset::GBK);
};


string Charset::Convert(const string& str, int fromCode, int toCode)
{
    string from = Charset::GetCodeName(fromCode);
    string to = Charset::GetCodeName(toCode);
    if (from.empty() || to.empty())
    {
        return str;
    }
    return Charset::Convert(str, from, to);
};


string Charset::Convert(const string& fromstr, const string& from_code, const string& to_code)
{
    string strOutParam;
    char buff[1024+1] = {0};
    size_t iDesLen = sizeof(buff);
    int iRet = Charset::Convert(const_cast<char*> (fromstr.c_str()), buff, iDesLen, from_code.c_str(), to_code.c_str());
    if(iRet == 0)
    {
        strOutParam = buff;
    }
    else
    {
        strOutParam = fromstr;
    }
    return strOutParam;
};

int Charset::Convert(const char * pSrc, char * pDest, size_t& iDestLen, const char * from_code, const char * to_code)
{
    iconv_t id = iconv_open(to_code, from_code);
    if((iconv_t) - 1 == id)
    {
        return -2;
    }
    size_t iSrcLen = strlen(pSrc);
    char* ptrInput = (char*)pSrc;
    char* ptrOutput = pDest;
    //iconv函数结束后， ptrOutput 会指向转换后编码的末尾，并且不会置0。iDestLen是ptrOutput缓存剩余的长度，实际转换后编码的长度 = ptrOutput缓存长度 - iDestLen
    if(iconv(id, &ptrInput, &iSrcLen, &ptrOutput,  &iDestLen) == (size_t) - 1)
    {
        iconv_close(id);
        return -1;
    }
    *ptrOutput = 0;
    iconv_close(id);
    return 0;
}


string Charset::Charset::GetCodeName(int code)
{
    switch(code)
    {
    case GBK :
        return "GBK";
    case UTF8 :
        return "UTF-8";
    default:
        return "";

    }
}


bool Charset::IsUTF8(const string& str)   
{   
    bool isUTF8 = true;   
    unsigned char* start = (unsigned char*)str.c_str();
    unsigned char* end = (unsigned char*)str.c_str() + str.size();
    while (start < end)   
    {   
        if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符   
        {   
            //isUTF8 = false;
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



bool Charset::IsUTF8(const string& str, bool includeNum, bool includeAlpha)
{
    bool isUTF8 = true;   
    unsigned char* start = (unsigned char*)str.c_str();
    unsigned char* end = (unsigned char*)str.c_str() + str.size();
    while (start < end)   
    {   
        if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符   
        {
            if(*start >=0x30 && *start<=0x39)  //0-9
            {
                if (!includeNum)
                {
                    isUTF8 = false;
                    cout << "num/char:" << *start << endl;
                    break;
                }
            }
            else if ((*start >=0x61 && *start<=0x7A) ||  //a-z
                    (*start >=0x41 && *start<=0x5A))    //A-Z
            {
                if (!includeAlpha)
                {
                    isUTF8 = false;
                    cout << "num/char:" << *start << endl;
                    break;
                }
                
            }
            else
            {
                cout << "not num/char:[" << *start  << "]"<< endl;
                isUTF8 = false;
                break;
            }
            
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