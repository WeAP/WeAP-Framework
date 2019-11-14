#ifndef __WeAP_Error_H__
#define __WeAP_Error_H__

#include "Object.h"

namespace WeAP { namespace System {


class Error : public Object
{
private:
    Error();

public:

    static const int ObjectList_Get_Out_Of_Range      = 10000;
    
    static const int FileUtil_Open_Failed             = 10001;

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

    static const int BASE64_Decode_Failed             = 10060;
    static const int BASE64_Encode_Failed             = 10061;
    static const int BASE64_EncodeFile_Failed         = 10062;
    static const int BASE64_DecodeFile_Failed         = 10063;
    static const int BASE64_DecodeBlock_Failed        = 10064;

    static const int INIConfig_Formate_Error          = 10070;


    static const int Convert_HexToChar_Failed         = 10080;


    static const int TextCodec_UrlDecode_Failed       = 10090;


    static const int MySQL_Init_Failed                = 10100;
    static const int MySQL_Connect_Failed             = 10101;
    static const int MySQL_Query_Failed               = 10102;
    static const int MySQL_NOT_IN_TRANS               = 10103;
    static const int MySQL_Affected_Rows_Error        = 10104;
    static const int MySQL_Result_NULL                = 10105;
    static const int MySQL_Begin_Failed               = 10106;
    static const int MySQL_Connection_Lost            = 10107;
    static const int MySQL_Commit_Lost_Connection     = 10108;
    static const int MySQL_Unknown_Error              = 10109;
    static const int MySQL_Query_Rows_Not_One         = 10110;
    static const int MySQL_Query_Rows_Zero            = 10111;

    static const int ProcessMutex_Lock_Failed         = 10120;
    static const int ProcessMutex_Unlock_Failed       = 10121;

    static const int ProcessSpin_Lock_Failed          = 10122;
    static const int ProcessSpin_Unlock_Failed        = 10123;

    

    static void Init(int appCode); 
    static int ToAppError(int error);

public:
    static int appCode;  ///< app code

};

}}

#endif

