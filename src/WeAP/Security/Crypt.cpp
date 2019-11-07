#include "Crypt.h"

using namespace std;

namespace WeAP { namespace System {


void Crypt::EncryptDesEde3(unsigned char* in, int inlen, unsigned char* out, int* outlen, const string& password)
{    
    const EVP_CIPHER * cipher = EVP_des_ede3( ); 
    if(cipher==NULL)
    {
        string errInfo = "::EVP_des_ede3 return NULL. "; 
        throw Exception(Error::Crypt_EncryptDesEde3_Failed,errInfo);  
    }

    unsigned char key[EVP_MAX_KEY_LENGTH];    //保存密钥的数组
    unsigned char iv[EVP_MAX_KEY_LENGTH];    //保存初始化向量的数组    
    EVP_BytesToKey(cipher,EVP_md5(),NULL,(const unsigned char *)password.c_str(),password.size(),1,key,iv);  //根据口令、密码算法生成key和iv

    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
    int rv = EVP_EncryptInit_ex(&ctx,cipher,NULL,key,iv);  //设置密码算法、key和iv
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        string errInfo = "::EVP_EncryptInit_ex error. "; 
        throw Exception(Error::Crypt_EncryptDesEde3_Failed,errInfo);
    }
  
    rv = EVP_EncryptUpdate(&ctx,out, outlen, in, inlen);//加密
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        string errInfo = "::EVP_EncryptUpdate error. "; 
        throw Exception(Error::Crypt_EncryptDesEde3_Failed,errInfo);
    }
    
    rv = EVP_EncryptFinal_ex(&ctx,out, outlen); //加密结束
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        string errInfo = "::EVP_EncryptFinal_ex error. "; 
        throw Exception(Error::Crypt_EncryptDesEde3_Failed,errInfo);
    }

    EVP_CIPHER_CTX_cleanup(&ctx);//清除EVP加密上下文环境
}

void Crypt::DecryptDesEde3(unsigned char* in, int inlen, unsigned char* out, int* outlen, const string& password)
{        
    const EVP_CIPHER * cipher = EVP_des_ede3( ); 
    if(cipher==NULL)
    {
        string errInfo = "::EVP_des_ede3 return NULL. "; 
        throw Exception(Error::Crypt_DecryptDesEde3_Failed,errInfo);    
    }
   
    unsigned char key[EVP_MAX_KEY_LENGTH];        //保存密钥的数组
    unsigned char iv[EVP_MAX_KEY_LENGTH];        //保存初始化向量的数组                    
    EVP_BytesToKey(cipher,EVP_md5(),NULL,(const unsigned char *)password.c_str(),password.size(),1,key,iv);  //根据口令、密码算法生成key和iv
    
    EVP_CIPHER_CTX ctx;        
    EVP_CIPHER_CTX_init(&ctx);        
    int rv = EVP_DecryptInit_ex(&ctx,cipher,NULL,key,iv); //设置解密的算法、key和iv
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        string errInfo = "::EVP_DecryptInit_ex error. "; 
        throw Exception(Error::Crypt_DecryptDesEde3_Failed,errInfo);    
    }     
            
    rv = EVP_DecryptUpdate(&ctx,out, outlen, in, inlen);//解密
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        string errInfo = "::EVP_DecryptUpdate error. "; 
        throw Exception(Error::Crypt_DecryptDesEde3_Failed,errInfo);   
    }

    rv = EVP_DecryptFinal_ex(&ctx,out,outlen);
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        string errInfo = "::EVP_DecryptFinal_ex error. "; 
        throw Exception(Error::Crypt_DecryptDesEde3_Failed,errInfo); 
    }
    
    EVP_CIPHER_CTX_cleanup(&ctx);
}


void Crypt::EncryptFileDesEde3(const string& plainFilePath, const string& cipherFilePath, const string& password)
{      
    const EVP_CIPHER * cipher = EVP_des_ede3( ); 
    if(cipher==NULL)
    {
        string errInfo = "::EVP_des_ede3 return NULL. "; 
        throw Exception(Error::Crypt_EncryptFileDesEde3_Failed,errInfo);                
    }    

    FILE* fpIn = fopen(plainFilePath.c_str(),"rb");
    if(fpIn == NULL)
    {
        string errInfo = "::fopen error, fileName=" + plainFilePath; 
        throw Exception(Error::Crypt_EncryptFileDesEde3_Failed,errInfo);  
    }

    FILE* fpOut = fopen(cipherFilePath.c_str(),"wb");
    if(fpOut == NULL)
    {        
        fclose(fpIn);
        string errInfo = "::fopen error, fileName=" + cipherFilePath; 
        throw Exception(Error::Crypt_EncryptFileDesEde3_Failed,errInfo);  
    }

    unsigned char key[EVP_MAX_KEY_LENGTH];    //保存密钥的数组
    unsigned char iv[EVP_MAX_KEY_LENGTH];    //保存初始化向量的数组    
    EVP_BytesToKey(cipher,EVP_md5(),NULL,(const unsigned char *)password.c_str(),password.size(),1,key,iv);  //根据口令、密码算法生成key和iv

    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
    int rv = EVP_EncryptInit_ex(&ctx,cipher,NULL,key,iv);  //设置密码算法、key和iv
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        string errInfo = "::EVP_EncryptInit_ex error"; 
        throw Exception(Error::Crypt_EncryptFileDesEde3_Failed,errInfo);  
    }

    unsigned char out[1024] = {0};                //保存密文的缓冲区
    int outl = 0;
    unsigned char in[1024] = {0};                    //保存原文的缓冲区
    int inl = 0;    

    //以1K为单位，循环读取原文，加密后后保存到密文文件。
    for(;;)
    {
        inl = fread(in,1,1024,fpIn);
        if(inl <= 0)//读取原文结束
            break;
        rv = EVP_EncryptUpdate(&ctx,out,&outl,in,inl);//加密
        if(rv != 1)
        {
            fclose(fpIn);
            fclose(fpOut);
            EVP_CIPHER_CTX_cleanup(&ctx);
            string errInfo = "::EVP_EncryptUpdate error"; 
            throw Exception(Error::Crypt_EncryptFileDesEde3_Failed,errInfo);  
        }
        fwrite(out,1,outl,fpOut);//保存密文到文件
    }
    
    rv = EVP_EncryptFinal_ex(&ctx,out,&outl); //加密结束
    if(rv != 1)
    {
        fclose(fpIn);
        fclose(fpOut);
        EVP_CIPHER_CTX_cleanup(&ctx);
        string errInfo = "::EVP_EncryptFinal_ex error"; 
        throw Exception(Error::Crypt_EncryptFileDesEde3_Failed,errInfo);  
    }
    fwrite(out,1,outl,fpOut);//保密密文到文件
    fclose(fpIn);
    fclose(fpOut);
    EVP_CIPHER_CTX_cleanup(&ctx);//清除EVP加密上下文环境    
}

void Crypt::DecryptFileDesEde3(const string& cipherFilePath, const string& plainFilePath, const string& password)
{           
    const EVP_CIPHER * cipher = EVP_des_ede3( ); 
    if(cipher==NULL)
    {
        string errInfo = "::EVP_des_ede3 return NULL."; 
        throw Exception(Error::Crypt_DecryptFileDesEde3_Failed,errInfo);    
    }

    FILE* fpIn = fopen(cipherFilePath.c_str(),"rb");
    if(fpIn == NULL)
    {
        string errInfo = "::fopen error, fileName=" + cipherFilePath; 
        throw Exception(Error::Crypt_DecryptFileDesEde3_Failed,errInfo);    
    }

    FILE* fpOut = fopen(plainFilePath.c_str(),"wb");
    if(fpOut == NULL)
    {
        fclose(fpIn);
        string errInfo = "::fopen error, fileName=" + plainFilePath; 
        throw Exception(Error::Crypt_DecryptFileDesEde3_Failed,errInfo);  
    }
    
    unsigned char key[EVP_MAX_KEY_LENGTH];        //保存密钥的数组
    unsigned char iv[EVP_MAX_KEY_LENGTH];        //保存初始化向量的数组                    
    EVP_BytesToKey(cipher,EVP_md5(),NULL,(const unsigned char *)password.c_str(),password.size(),1,key,iv);  //根据口令、密码算法生成key和iv
    
    EVP_CIPHER_CTX ctx;        
    EVP_CIPHER_CTX_init(&ctx);        
    int rv = EVP_DecryptInit_ex(&ctx,cipher,NULL,key,iv); //设置解密的算法、key和iv
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        
        string errInfo = "::EVP_DecryptInit_ex error"; 
        throw Exception(Error::Crypt_DecryptFileDesEde3_Failed,errInfo);  
    }

    unsigned char out[1024+EVP_MAX_KEY_LENGTH] = {0};    //保存解密后明文的缓冲区数组
    int outl = 0;
    unsigned char in[1024] = {0};                        //保存密文数据的数组
    int inl = 0;

    //以1K为单位，循环读取原文，解密后后保存到明文文件。
    for(;;)
    {
        inl = fread(in,1,1024,fpIn);
        if(inl <= 0)
            break;
        rv = EVP_DecryptUpdate(&ctx,out,&outl,in,inl);//解密
        if(rv != 1)
        {
            fclose(fpIn);
            fclose(fpOut);
            EVP_CIPHER_CTX_cleanup(&ctx);

            string errInfo = "::EVP_DecryptUpdate error"; 
            throw Exception(Error::Crypt_DecryptFileDesEde3_Failed,errInfo); 
        }
        fwrite(out,1,outl,fpOut);//保存明文到文件
    }

    rv = EVP_DecryptFinal_ex(&ctx,out,&outl);
    if(rv != 1)
    {
        fclose(fpIn);
        fclose(fpOut);
        EVP_CIPHER_CTX_cleanup(&ctx);
        
        string errInfo = "::EVP_DecryptFinal_ex error"; 
        throw Exception(Error::Crypt_Crypt_DecryptFileDesEde3_Failed,errInfo); 
    }
    fwrite(out,1,outl,fpOut);//保存明文到文件
    fclose(fpIn);
    fclose(fpOut);
    EVP_CIPHER_CTX_cleanup(&ctx);     
}


}}