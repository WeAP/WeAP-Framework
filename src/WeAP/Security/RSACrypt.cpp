#include "RSACrypt.h"
#include "Error.h"
#include "Exception.h"
#include "Logger.h"

using namespace WeAP::System;

namespace WeAP { namespace Security {

RSACrypt::RSACrypt()
{
    //加载加密算法
    ::OpenSSL_add_all_algorithms();
    
    this->rsa = ::RSA_new(); 
    if (NULL == this->rsa)
    {
        string errInfo = "::RSA_new err, " + GetError();
        ERROR("%s", errInfo.c_str());   
        throw Exception(Error::RSA_Init_Failed,errInfo); 
    }
}

RSACrypt::~RSACrypt()
{        
    if (this->rsa != NULL)
    {
        ::RSA_free(this->rsa);
        this->rsa = NULL;
    }
}

string RSACrypt::GetCertSerialNumber(const string& certFilePath, const string& password)
{
    BIO* bio = ::BIO_new_file(certFilePath.c_str(), "rb");
    if (NULL == bio)  
    {  
        string errInfo = "GetCertSerialNumber ::BIO_new_file err,filePath=" + certFilePath; 
        throw Exception(Error::RSA_Get_CertSN_Failed,errInfo);    
    }
   
    //pem_password_cb* cb = passphrase_cb;
    pem_password_cb* cb = NULL;
    X509* x509 = NULL;
    x509 = ::PEM_read_bio_X509(bio, &x509, cb, (void *)password.c_str());
    BIO_free(bio);
    if(x509 == NULL)
    {
        string errInfo = "GetCertSerialNumber ::PEM_read_bio_X509 err," + this->GetError(); 
        throw Exception(Error::RSA_Get_CertSN_Failed,errInfo);
    }

    ASN1_INTEGER* serialNumber = ::X509_get_serialNumber(x509);
    
    BIGNUM   *bn = NULL;
    bn = ::ASN1_INTEGER_to_BN(serialNumber, NULL);
    X509_free(x509);
    if(bn == NULL)
    {
        string errInfo = "GetCertSerialNumber ::ASN1_INTEGER_to_BN err," + this->GetError(); 
        ERROR("%s", errInfo.c_str());
        throw Exception(Error::RSA_Get_CertSN_Failed, errInfo);
    }
    char  *serialHex;
    serialHex= ::BN_bn2hex(bn);
    BN_free(bn);  
    if(serialHex == NULL)
    {
        string errInfo = "GetCertSerialNumber ::BN_bn2hex err," + this->GetError(); 
        ERROR("%s", errInfo.c_str());
        throw Exception(Error::RSA_Get_CertSN_Failed,errInfo); 
    }
    string serialHexStr= serialHex;
    OPENSSL_free(serialHex);  
    return serialHexStr;

}

/*    
void RSACrypt::GenerateKey()
{
    int bits=1024;
    
    BIGNUM *bne = ::BN_new();
    unsigned long e = RSA_3;
    int ret = ::BN_set_word(bne,e);                
    ret = ::RSA_generate_key_ex(this->rsa,bits,bne,NULL);
    ::BN_free(bne);
    if(ret!=1)
    { 
        throw Exception(Error::RSA_GenerateKey_Failed,"GenerateKey err");            
    }

}
*/
void RSACrypt::ReadPublicKeyFromCert(const string& certFilePath, const string& password)
{
    BIO* bio = ::BIO_new_file(certFilePath.c_str(), "rb");
    if (NULL == bio)  
    {  
        string errInfo = "ReadPublicKeyFromCert ::BIO_new_file err,filePath" + certFilePath;    
        throw Exception(Error::RSA_PublicKey_Read_Failed,errInfo);    
    }

    //pem_password_cb* cb = passphrase_cb;
    pem_password_cb* cb = NULL;

    //从证书中读取公钥        
    X509 *x509 = ::PEM_read_bio_X509(bio, NULL, cb, (void *)password.c_str()); 
    BIO_free(bio);
    if (NULL == x509)
    {
        throw Exception(Error::RSA_PublicKey_Read_Failed, "ReadPublicKeyFromCert ::PEM_read_X509 fail !");    
    }
    
    EVP_PKEY* pubkey = ::X509_get_pubkey(x509);
    X509_free(x509);
    if (pubkey == NULL)
    {             
        throw Exception(Error::RSA_PublicKey_Read_Failed, "ReadPublicKeyFromCert ::X509_get_pubkey fail !");    
    }      
    
    if (this->rsa != NULL)
    {
        ::RSA_free(this->rsa);
        this->rsa = NULL;
    }

    this->rsa = ::EVP_PKEY_get1_RSA(pubkey);
    EVP_PKEY_free(pubkey);
    if (this->rsa == NULL)
    {           
        string errInfo = "ReadPublicKeyFromCert ::EVP_PKEY_get1_RSA fail ! err," + this->GetError();    
        throw Exception(Error::RSA_PublicKey_Read_Failed, errInfo);
    }

}

void RSACrypt::ReadPrivateKey(const string& filePath, const string& password)
{ 
    BIO* bio = ::BIO_new_file(filePath.c_str(), "rb");
    if (NULL == bio)  
    {  
        string errInfo = "ReadPrivateKey ::BIO_new_file err,filePath" +filePath;    
        throw Exception(Error::RSA_PrivateKey_Read_Failed, errInfo);    
    }

    //pem_password_cb* cb = passphrase_cb;
    pem_password_cb* cb = NULL;
    rsa = ::PEM_read_bio_RSAPrivateKey(bio, &this->rsa, cb, (void *)password.c_str());  
    BIO_free(bio);
    if(this->rsa == NULL)
    {
        string tmp = this->GetError();
        ERROR("RSA::ReadPrivateKey::GetLastErrorMesage=[%s]", tmp.c_str() ); 
        string errInfo = "ReadPrivateKey::PEM_read_bio_RSAPrivateKey rsa return NULL" + tmp;    
        throw Exception(Error::RSA_PrivateKey_Read_Failed, errInfo);
    }  


    if(this->rsa->d == NULL)
    {
        string tmp = this->GetError();
        ERROR("RSA::ReadPrivateKey::GetLastErrorMesage=[%s]", tmp.c_str() ); 
        string errInfo = "ReadPrivateKey::PEM_read_bio_RSAPrivateKey rsa->d return NULL" + tmp;    
        throw Exception(Error::RSA_PrivateKey_Read_Failed, errInfo);

    }    


};

void RSACrypt::WritePrivateKey(const string& filePath, const string& password)
{        
    BIO* bio = BIO_new_file(filePath.c_str(), "w");
    const EVP_CIPHER* enc = NULL;
    unsigned char *kstr = NULL;
    int klen = 0;
    pem_password_cb* cb = NULL;
    int ret = ::PEM_write_bio_RSAPrivateKey(bio, this->rsa, enc, kstr, klen, cb, (void *)password.c_str());
    if (ret != 1)
    {
        BIO_free(bio);
        string errInfo = "PEM_write_bio_RSAPrivateKey err,filePath" +filePath;    
        throw Exception(Error::RSA_PrivateKey_Write_Failed,errInfo);    
    }

    ret = BIO_flush(bio);  //BIO_flush() returns 1 for success and 0 or -1 for failure.
    if (ret != 1)
    {
        BIO_free(bio);
        string errInfo = "BIO_flush err,filePath" + filePath;    
        throw Exception(Error::RSA_PrivateKey_Write_Failed, errInfo);    
    }
    BIO_free(bio);
}

void RSACrypt::PrivateEncrypt(unsigned char* plainText, unsigned char* cipherText, int& cipherTextLength)
{
    if (plainText == NULL)
    {
        throw Exception(Error::RSA_PrivateEncrypt_Failed,"PrivateEncrypt param null");
    }

    //int plainTextLength = ::RSA_size(this->rsa);  //128
    int plainTextLength = ::strlen((const char *)plainText); 
    this->PrivateEncrypt(plainText, plainTextLength, cipherText, cipherTextLength);
}

void RSACrypt::PrivateEncrypt(unsigned char* plainText, int plainTextLength, unsigned char* cipherText, int& cipherTextLength)
{     
    if (plainText == NULL)
    {
        throw Exception(Error::RSA_PrivateEncrypt_Failed,"PrivateEncrypt param null");
    }

    cipherTextLength = ::RSA_private_encrypt(plainTextLength, plainText, cipherText, this->rsa, RSA_PKCS1_PADDING);
    if(cipherTextLength <= 0)
    {
        string errInfo = "::RSA_private_encrypt err," + this->GetError();    
        throw Exception(Error::RSA_PrivateEncrypt_Failed,errInfo);
    }

}

void RSACrypt::PublicEncrypt(unsigned char* plainText, int plainTextLength, unsigned char* cipherText, int& cipherTextLength)
{        
    if (plainText == NULL)
    {
        throw Exception(Error::RSA_PublicEncrypt_Failed,"PublicEncrypt param null");
    }
    
    cipherTextLength = RSA_public_encrypt(plainTextLength, plainText, cipherText, this->rsa, RSA_PKCS1_PADDING);
    if(cipherTextLength <= 0)
    {
        string errInfo = "::RSA_private_encrypt err," + this->GetError();    
        throw Exception(Error::RSA_PublicEncrypt_Failed,errInfo);
    }
}

void RSACrypt::PrivateDecrypt(unsigned char* cipherText, int cipherTextLength, unsigned char* plainText)
{    
    if (cipherText == NULL)
    {
        throw Exception(Error::RSA_PrivateDecrypt_Failed,"PrivateDecrypt param null");
    }

    int ret = ::RSA_private_decrypt(cipherTextLength, cipherText, plainText, this->rsa, RSA_PKCS1_PADDING);
    if(ret <= 0)
    {
        string errInfo = "::RSA_private_decrypt err," + this->GetError();            
        throw Exception(Error::RSA_PrivateDecrypt_Failed,errInfo);
    }        
}
    
void RSACrypt::PublicDecrypt(unsigned char* cipherText, int cipherTextLength, unsigned char* plainText)
{   
    if (cipherText == NULL)
    {
        throw Exception(Error::RSA_PublicDecrypt_Failed,"PublicDecrypt param null");
    }

    int ret = ::RSA_public_decrypt(cipherTextLength, cipherText, plainText, this->rsa, RSA_PKCS1_PADDING);
    if(ret <= 0)
    {
        string errInfo = "::RSA_public_decrypt err," + this->GetError();            
        throw Exception(Error::RSA_PublicDecrypt_Failed,errInfo);
    }
}

string RSACrypt::GetError()
{
    unsigned long errCode = ERR_get_error();
    char errMsg[1024] = {0};
    ERR_error_string(errCode, errMsg);
    return string(errMsg);
}





}}
