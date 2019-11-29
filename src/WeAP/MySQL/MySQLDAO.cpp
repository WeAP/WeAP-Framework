#include "MySQLDAO.h"



namespace WeAP { namespace MySQL {

MySQLDAO::MySQLDAO()
{
}

MySQLDAO::~MySQLDAO()
{

}

void MySQLDAO::Init(const INIConfig& config, const string& section)
{
    const KVMap& kvmap = config.GetSection(section);
    this->ip = kvmap.GetString("Host");
    this->port = kvmap.GetInt32("Port");
    this->userName = kvmap.GetString("UserName");
    this->password = kvmap.GetString("Password");
    this->connTimeoutMs = kvmap.GetInt32("ConnTimeout");
    this->rwTimeoutMs = kvmap.GetInt32("RWTimeout");
    int idleTime = 8000;
    string charset = "utf8";
    string dbName;

    this->mysql.Init(this->ip,
                     this->port,
                     this->userName,
                     this->password,
                     idleTime, 
                     this->connTimeoutMs / 1000, 
                     this->rwTimeoutMs / 1000,
                     charset,
                     dbName);

}

void MySQLDAO::Query(const string& sql, KVMap& record)
{
    this->mysql.Query(sql, record);
}
void MySQLDAO::Query(const string& sql, ObjectList<KVMap>& recordList)
{
    this->mysql.Query(sql, recordList);
}

void MySQLDAO::Insert(const string& sql)
{
    this->mysql.Insert(sql);
}

}}
