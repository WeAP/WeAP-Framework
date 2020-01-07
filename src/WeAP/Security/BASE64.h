
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
#include "Object.h"

using namespace std;
using namespace WeAP::System;

namespace WeAP { namespace Security {


class BASE64: public Object
{
private:
    BASE64();
    
public:

    static string Encode(const string& str);
    static string Decode(const string& str);

    static void Encode(unsigned char* data, int datalen, unsigned char* outData, int *outlen);
    static void Decode(unsigned char* data, int datalen, unsigned char* outData, int *outlen);

    static void EncodeFile(const string& inFilePath, const string& outFilePath);
    static void DecodeFile(const string& inFilePath, const string& outFilePath);

    static string EncodeBlock(const char *s, size_t len);
    static string DecodeBlock(const char *s, size_t len);


};

}}
#endif

