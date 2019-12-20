
#ifndef __WeAP_MySQL_H__
#define __WeAP_MySQL_H__

#include <mysql.h>
#include <mysqld_error.h>
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Error.h"
#include "Exception.h"
#include "KVMap.h"
#include "MySQLResult.h"

using namespace std;

namespace WeAP { namespace MySQL {


/**
 *
 * @ref https://dev.mysql.com/doc/refman/5.7/en/mysql-real-connect.html 
 */
class MySQL
{
public:
    static string EscapeString(const string& buff);
    static string GetString(char *str);

public:
    MySQL();    
    virtual ~MySQL();

    void Init(const std::string& ip,
              int port,
              const std::string& user, 
              const std::string& passwd, 
              int waitTimeoutS, 
              int connTimeoutS = 5,
              int rwTimeoutS = 5,
              const std::string& charset = "utf8", 
              const std::string& dbName = "");

    void Query(const string& sql, KVMap& record, bool removePrefixF = false);
    void Query(const string& sql, ObjectList<KVMap>& recordList, bool removePrefixF = false);

    //void Query(const string& sql);
    void Insert(const string& sql);
    void Update(const string& sql);

    void BatchQuery(const string& sql);
    void BatchInsert(const string& sql);
    void BatchUpdate(const string& sql);

    void Execute(const string& sql);

    unsigned long AffectedRows();
    MYSQL_RES* FetchResult();

    int  FetchRows();

    void Begin();
    void Commit();
    void Rollback();

    bool Ping(); 

protected:
    void Connect();
    void Close();

    void TransBegin();
    void TransEnd();
    bool IsTrans();    
    void CheckTrans();

    void SetWaitTimeout();

    void Query(const string& sql);

    int RealQuery(const string& sql);

    string GetDBError();

private:
    MySQL(const MySQL& other);
    MySQL& operator=(const MySQL& other);

protected:
    std::string ip;
    int port;
    std::string user;
    std::string passwd;
    std::string dbName;    
    uint32_t connTimeoutS;
    uint32_t rwTimeoutS;
    uint32_t waitTimeoutS;
    int  idleTime;
    std::string charset;

    MYSQL* mysql;

    bool isConnected;
    bool isTrans;

};

}}

#endif

