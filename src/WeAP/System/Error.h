#ifndef __WeAP_Error_H__
#define __WeAP_Error_H__

#include "Object.h"

namespace WeAP { namespace System {


class Error : public Object
{
private:
    Error();

public:

    static const int ERR_OBJECT_LIST_GET_OUT_OF_RANGE = 10000;
    
    static const int ERR_FILE_UTIL_OPEN_FAILED        = 10001;

    static const int RegexMatch_Failed                = 10002;

    static const int RSA_Init_Failed                  = 10020;
    static const int RSA_Get_CertSN_Failed            = 10021;
    static const int RSA_PrivateKey_Read_Failed       = 10022;
    static const int RSA_PrivateKey_Write_Failed      = 10023;
    static const int RSA_PrivateEncrypt_Failed        = 10024;
    static const int RSA_PrivateDecrypt_Failed        = 10025;
    static const int RSA_PublicKey_Read_Failed        = 10026;
    static const int RSA_PublicEncrypt_Failed         = 10027;
    static const int RSA_PublicDecrypt_Failed         = 10028;

    static const int Crypt_EncryptDesEde3_Failed      = 10040;
    static const int Crypt_DecryptDesEde3_Failed      = 10041;
    static const int Crypt_EncryptFileDesEde3_Failed  = 10042;
    static const int Crypt_DecryptFileDesEde3_Failed  = 10043;

    static const int BASE64_EncodeFile_Failed         = 10060;
    static const int BASE64_DecodeFile_Failed         = 10060;


    static void Init(int appCode); 
    static int ToAppError(int error);

public:
    static int appCode;  ///< app code

};

}}

#endif

