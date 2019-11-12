#ifndef __WeAP_RSACrypt_H__
#define __WeAP_RSACrypt_H__

#include "Object.h"
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <sstream>

#include <openssl/objects.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/md5.h>
#include <openssl/err.h>

using namespace WeAP::System;

namespace WeAP { namespace Security {

/**
 * 
 * 
 * @author xzwang
 */
class RSACrypt : public Object
{
public:
    RSACrypt();
    virtual ~RSACrypt();


private:
    RSACrypt(const RSACrypt& other);
    RSACrypt& operator=(const RSACrypt& other);

public:
    string GetCertSerialNumber(const string& certFilePath, const string& password="");

        
    //void GenerateKey();
    
    void ReadPublicKeyFromCert(const string& certFilePath, const string& password="");

    void ReadPrivateKey(const string& filePath, const string& password="");

    void WritePrivateKey(const string& filePath, const string& password="");

    void PrivateEncrypt(unsigned char* plainText, unsigned char* cipherText, int& cipherTextLength);
    
    void PrivateEncrypt(unsigned char* plainText, int plainTextLength, unsigned char* cipherText, int& cipherTextLength);

    void PublicEncrypt(unsigned char* plainText, int plainTextLength, unsigned char* cipherText, int& cipherTextLength);

    void PrivateDecrypt(unsigned char* cipherText, int cipherTextLength, unsigned char* plainText);
        
    void PublicDecrypt(unsigned char* cipherText, int cipherTextLength, unsigned char* plainText);

protected:
    string GetError();

protected:    
    ::RSA* rsa;

};

}}


#endif //__WeAP_RSACrypt_H__

