
#ifndef __WeAP_MySQLDB_H__
#define __WeAP_MySQLDB_H__

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

class Sql
{
public:
    Sql(){};
    virtual ~Sql(){};

    Sql& Append(const string& str)
    {
        this->sql << str << " ";
        return *this;
    };


    Sql& AppendValue(int32_t value, bool withComma = true)
    {
        this->sql << value;
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };
    Sql& AppendValue(uint32_t value, bool withComma = true)
    {
        this->sql << value;
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };
    Sql& AppendValue(int64_t value, bool withComma = true)
    {
        this->sql << value;
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };
    Sql& AppendValue(uint64_t value, bool withComma = true)
    {
        this->sql << value;
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };

    Sql& AppendValue(const string& value, bool withComma = true)
    {
        this->sql << "'" << value << "'";
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };

    Sql& AppendValue(const string& name, int32_t value, bool withComma = true)
    {
        this->sql << name << "=" << value;
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };
    Sql& AppendValue(const string& name, uint32_t value, bool withComma = true)
    {
        this->sql << name << "=" << value;
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };
    Sql& AppendValue(const string& name, int64_t value, bool withComma = true)
    {
        this->sql << name << "=" << value;
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };
    Sql& AppendValue(const string& name, uint64_t value, bool withComma = true)
    {
        this->sql << name << "=" << value;
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };
    Sql& AppendValue(const string& name, const string& value, bool withComma = true)
    {
        this->sql << name << "='" << value << "'";
        if (withComma)
        {
            this->sql << ",";
        }
        return *this;
    };

    string ToString()
    {
        return this->sql.str();
    }

protected:
    stringstream sql;

};



/**
 *
 * @ref https://dev.mysql.com/doc/refman/5.7/en/mysql-real-connect.html 
 */
class MySQLDB
{
public:
    static string EscapeString(const string& buff);
    static string GetString(char *str);

public:
    MySQLDB();    
    virtual ~MySQLDB();

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
    MySQLDB(const MySQLDB& other);
    MySQLDB& operator=(const MySQLDB& other);

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

