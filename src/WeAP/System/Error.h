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

    static const int Mutex_Lock_Failed                = 10125;
    static const int Mutex_TryLock_Failed             = 10126;
    static const int Mutex_Unlock_Failed              = 10127;

    static const int RWLock_RLock_Failed              = 10128;
    static const int RWLock_WLock_Failed              = 10129;
    static const int RWLock_Unlock_Failed             = 10130;
    
    
    
    
    

    static const int Socket_Create_Failed             = 10200;
    static const int Socket_Connect_Failed            = 10201;
    static const int Socket_Get_Peer_Name_Failed      = 10202;
    static const int Socket_Get_Sock_Name_Failed      = 10203;
    static const int Socket_Set_Sock_Opt_Failed       = 10204;
    static const int Socket_Accept_Failed             = 10205;
    static const int Socket_Get_In_Addr_Failed        = 10206;
    static const int Socket_Bind_Failed               = 10207;
    static const int Socket_Listen_Failed             = 10208;
    static const int Socket_Receive_From_Failed       = 10209;
    static const int Socket_Send_Failed               = 10209;
    static const int Socket_Send_To_Failed            = 10209;
    static const int Socket_Set_Nonblock_Failed       = 10209;
    static const int Socket_Gets_Failed               = 10209;
    static const int Socket_Receive_Failed            = 10209;
    static const int Socket_ShutDown_Failed           = 10209;

    static const int Redis_Connect_Failed             = 10210;
    static const int Redis_Context_Is_NULL            = 10211;
    
    static const int Redis_Command_Failed             = 10220;
    static const int Redis_Command_Status_Failed      = 10221;
    static const int Redis_Command_Int_Failed         = 10222;
    static const int Redis_Command_String_Failed      = 10223;
    static const int Redis_Set_Failed                 = 10224;
    static const int Redis_Get_Failed                 = 10225;
    static const int Redis_Del_Failed                 = 10226;
    static const int Redis_HSet_Failed                = 10227;
    static const int Redis_HGet_Failed                = 10228;
    static const int Redis_HDel_Failed                = 10229;
    static const int Redis_Ping_Failed                = 10230;

    
    static const int JsonText_Parse_Failed            = 10240;
    static const int JsonText_Open_File_Failed        = 10241;
    static const int JsonText_Node_Is_NULL            = 10242;
    static const int JsonText_Node_Is_Empty_Or_NULL   = 10243;
    static const int JsonText_Node_Is_Not_String      = 10244;
    static const int JsonText_Node_Is_Not_Int         = 10245;
    static const int JsonText_Node_Is_Not_Uint        = 10246;
    static const int JsonText_Node_Is_Not_Double      = 10247;
    static const int JsonText_Node_Is_Not_Object      = 10248;
    static const int JsonText_Node_Is_Not_Array       = 10249;
    static const int JsonText_Array_Index_Is_Not_Valid= 10250;


    static const int CURL_Init_Failed                 = 10260;
    static const int CURL_Setopt_Failed               = 10261;
    static const int CURL_Perform_Failed              = 10262;


    static void Init(int appCode); 
    static int ToAppError(int error);

public:
    static int appCode;  ///< app code

};

}}

#endif

