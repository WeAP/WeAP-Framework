#ifndef __WeAP_MySQLDAO_H__
#define __WeAP_MySQLDAO_H__

#include "DAO.h"
#include "ObjectList.h"
#include "INIConfig.h"
#include "SQL.h"
#include "MySQL.h"
#include "MySQLTransaction.h"

using namespace WeAP::System;
using namespace WeAP::Framework;

namespace WeAP { namespace MySQL {


/**
 * 
 * 
 * @author xzwang
 */
class MySQLDAO : public DAO
{
public:
    MySQLDAO();
    virtual ~MySQLDAO();

    void Init(const INIConfig& config, const string& section);

    MySQL* GetTransHandler();

    MySQLTransaction GetTransaction();

    

protected:
    void Query(const string& sql, KVMap& record);
    void Query(const string& sql, ObjectList<KVMap>& recordList);

    void Insert(const string& sql, MySQLTransaction& trans);
    void Insert(const string& sql, MySQL* transHandler);

    void Update(const string& sql, MySQLTransaction& trans);
    void Update(const string& sql, MySQL* transHandler);

    string GetFullTableName(uint64_t key);
    



private:
    MySQLDAO(const MySQLDAO& other);
    MySQLDAO& operator=(const MySQLDAO& other);

protected:
    string ip;
    uint32_t port;
    uint32_t connTimeoutMs;
    uint32_t rwTimeoutMs;
    string userName;
    string password;

    MySQL mysql;

    string dbName;
    string tableName;
    string tableFields;
};

}}


#endif //__WeAP_MysqlDAO_H__

