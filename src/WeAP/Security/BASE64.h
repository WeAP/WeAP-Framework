
#ifndef __WeAP_BASE64_H__
#define __WeAP_BASE64_H__

#include <stdio.h>
#include <string>
#include <vector>

#include <openssl/objects.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/md5.h>


using namespace std;

namespace WeAP { namespace System {


class BASE64
{
private:
    BASE64();
    
public:

    static void EncodeFile(const string& inFilePath, const string& outFilePath);

    static void DecodeFile(const string& inFilePath, const string& outFilePath);

    static string EncodeBlock(const char *s, size_t len);

    static string DecodeBlock(const char *s, size_t len);

    static void Encode(unsigned char* str, int strLen, unsigned char* str64, int* str64Len);

    static void Decode(unsigned char* str, int str_len, unsigned char* decode, int* decode_len);    
    
    
    static int OpensslBase64Encode( unsigned char* outData,
                              int *outlen,
                              unsigned char* data,
                              int datalen );
    
    static int OpensslBase64Decode( unsigned char* outData,
                                      int * outlen,
                                      unsigned char* data,
                                      int datalen );

};

}}
#endif

