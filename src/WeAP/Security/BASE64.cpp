#include "BASE64.h"
#include "Error.h"
#include "Exception.h"
#include "Convert.h"
#include "Error.h"
#include "Exception.h"

using namespace std;
using namespace WeAP::System;

namespace WeAP { namespace Security {

string BASE64::Encode(const string& str)
{
    char outStr[1024] = {0};
    int outlen;
    BASE64::Encode((unsigned char*)str.c_str(), str.size(), (unsigned char*)outStr, &outlen);
    return string(outStr, outlen);
}
string BASE64::Decode(const string& str)
{
    char outStr[1024] = {0};
    int outlen;
    BASE64::Decode((unsigned char*)str.c_str(), str.size(), (unsigned char*)outStr, &outlen);
    return string(outStr, outlen);
}

void BASE64::Encode(unsigned char* data, int datalen, unsigned char* outData, int *outlen)
{
    EVP_ENCODE_CTX base64;
    EVP_EncodeInit(&base64); 
    EVP_EncodeUpdate(&base64, outData, outlen, data, datalen);
    int tmp = *outlen;
    EVP_EncodeFinal(&base64, outData + *outlen, outlen);
    *outlen += tmp;
    outData[*outlen] = 0;
}


void BASE64::Decode(unsigned char* data, int datalen, unsigned char* outData, int* outlen)
{
    EVP_ENCODE_CTX base64;
    EVP_DecodeInit(&base64);
    
    int i = EVP_DecodeUpdate(&base64, outData, outlen, data, datalen);
    if (i < 0)
    {
        string errMsg = "EVP_DecodeUpdate failed, ret=" + Convert::ToString(i);
        throw Exception(Error::BASE64_Decode_Failed, errMsg);
    }
    int tmp = *outlen;


    EVP_DecodeFinal(&base64, outData + tmp, outlen);
    //*outlen=tmp;
    *outlen += tmp;
    
    outData[*outlen] = 0;

}


void BASE64::EncodeFile(const string& inFilePath, const string& outFilePath)
{        
    FILE* infp = fopen(inFilePath.c_str(), "rb");
    if(infp == NULL)
    {
        string errInfo = "open file error, filePath=" + inFilePath;
        throw Exception(Error::BASE64_EncodeFile_Failed,errInfo);
    }
    
    FILE* outfp = fopen(outFilePath.c_str(),"w");
    if(outfp == NULL)
    {
        string errInfo = "open file error, filePath=" + outFilePath;
        fclose(infp);
        throw Exception(Error::BASE64_EncodeFile_Failed,errInfo);
    }

    EVP_ENCODE_CTX ctx;
    EVP_EncodeInit(&ctx);

    unsigned char in[1024] = {0};
    int inl = 0;
    char out[2048]={0};
    int outl = 0;

    while(1)
    {
        inl = fread(in,1,1024,infp);
        if(inl <= 0)
        {
            break;
        }
            
        EVP_EncodeUpdate(&ctx,(unsigned char *)out,&outl,(unsigned char *)in,inl);
        fwrite(out,1,outl,outfp);
    } 
    EVP_EncodeFinal(&ctx,(unsigned char *)out,&outl);
    fwrite(out,1,outl,outfp);

    fclose(infp);
    fclose(outfp);    
}

void BASE64::DecodeFile(const string& inFilePath, const string& outFilePath)
{        
    FILE* infp = fopen(inFilePath.c_str(),"r");
    if(infp == NULL)
    {
        string errInfo = "open file error, filePath=" + inFilePath;
        throw Exception(Error::BASE64_DecodeFile_Failed, errInfo);
    }

    FILE* outfp = fopen(outFilePath.c_str(),"wb");
    if(outfp == NULL)
    {
        string errInfo = "open file error, filePath=" + outFilePath;
        fclose(infp);
        throw Exception(Error::BASE64_DecodeFile_Failed,errInfo);
    }

    EVP_ENCODE_CTX ctx;
    EVP_DecodeInit(&ctx);

    char in[1024] = {0};
    int inl = 0;
    unsigned char out[1024] = {0};
    int outl = 0;
    int ret = 0;
    while(1)
    {
        inl = fread(in,1,1024,infp);
        if(inl <= 0)
        {
            break;
        }
        ret = EVP_DecodeUpdate(&ctx,out,&outl,(unsigned char *)in,inl);
        if (ret < 0)
        {
            break;
        }
        fwrite(out,1,outl,outfp);
    } 
    EVP_DecodeFinal(&ctx,out,&outl);
    fwrite(out,1,outl,outfp);
    fclose(infp);
    fclose(outfp);          
    if (ret < 0)
    {
        throw Exception(Error::BASE64_DecodeFile_Failed,"EVP_DecodeUpdate error");
    }
}
/*
string BASE64::EncodeBlock(const char *s, size_t len)
{        
    int expect_len = (len + 20) / 3 * 4; //32k
    char * result = new char[expect_len];  
    int out_len = 0;
    out_len = EVP_EncodeBlock((unsigned char *) result,
            (const unsigned char *) s, len);

    // delete '\n'
    if (out_len > 0 && result[out_len - 1] == '\n') {
        result[out_len - 1] = '\0';
        out_len--;
    }
    string ret(result, out_len);
    delete[] result;
    return ret;
}
*/
string BASE64::EncodeBlock(const char *s, size_t len)
{
    char result[32*1024] = {0};
    int out_len = 0;
    out_len = EVP_EncodeBlock((unsigned char *) result, (const unsigned char *) s, len);

    // delete '\n'
    if (out_len > 0 && result[out_len - 1] == '\n') {
        result[out_len - 1] = '\0';
        out_len--;
    }
    string ret(result, out_len);
    return ret;
}

/*
string BASE64::DecodeBlock(const char *s, size_t len)
{        
    int expect_len = len + 20;
    char * result = new char[expect_len];
    int out_len = EVP_DecodeBlock((unsigned char*) result,
            (const unsigned char *) s, len);
    if (out_len < 0) {
        delete[] result;
        //throw CException(ERR_ASSERT, "base64 decode error", __FILE__, __LINE__);
        return "";
    }
    if(len>=2&& s[len-1]=='=' && s[len-2]=='=' && out_len>=2 && result[out_len-1]=='\0' && result[out_len-2]=='\0')
    {
        out_len-=2;
    }
    else if(len>=1 && s[len-1]=='=' && out_len>=1 && result[out_len-1]=='\0')
    {
        out_len-=1;
    }
    //ɾ�� ĩβ'\0'
    //while (out_len > 0 && result[out_len - 1] == '\0') {
    //    out_len--;
    //}
    string ret(result, out_len);
    delete[] result;
    return ret;
}
*/

string BASE64::DecodeBlock(const char *s, size_t len)
{        
    char result[32*1024] = {0};
    int out_len = EVP_DecodeBlock((unsigned char*) result, (const unsigned char *) s, len);
    if (out_len < 0) 
    {
        throw Exception(Error::BASE64_DecodeBlock_Failed, "base64 decode error");
    }
    if(len>=2&& s[len-1]=='=' && s[len-2]=='=' && out_len>=2 && result[out_len-1]=='\0' && result[out_len-2]=='\0')
    {
        out_len-=2;
    }
    else if(len>=1 && s[len-1]=='=' && out_len>=1 && result[out_len-1]=='\0')
    {
        out_len-=1;
    }

    //while (out_len > 0 && result[out_len - 1] == '\0') {
    //    out_len--;
    //}
    string ret(result, out_len);
    return ret;
}

}}




