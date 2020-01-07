
#ifndef CryptH
#define CryptH

#include <fstream>
#include <openssl/bn.h>
#include <openssl/pem.h>
#include "Object.h"

using namespace std;
using namespace WeAP::System;

namespace WeAP { namespace Security {


/**
 * 对称加密工具
 * 
 * @author xzwang
 */
class Crypt: public Object
{
private:
    Crypt();
public:
    static void EncryptDesEde3(unsigned char* in, int inlen, unsigned char* out, int* outlen, const string& password);
    static void DecryptDesEde3(unsigned char* in, int inlen, unsigned char* out, int* outlen, const string& password);

    static void EncryptFileDesEde3(const string& plainFilePath, const string& cipherFilePath, const string& password);
    static void DecryptFileDesEde3(const string& cipherFilePath, const string& plainFilePath, const string& password);

};

}}


#endif

