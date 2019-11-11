
#include "MysqlDAO.h"

namespace WeAP { namespace Framework {

MysqlDAO::MysqlDAO()
{
}

MysqlDAO::~MysqlDAO()
{

}

void MysqlDAO::Init(const INIConfig& config, const string& section)
{
    KVMap kvmap;
    config.GetSection(section, kvmap);
    this->ip = kvmap.GetString("IP");
    this->port = kvmap.GetInt32("Port");
    this->connTimeoutMs = kvmap.GetInt32("ConnTimeout");
    this->rwTimeoutMs = kvmap.GetInt32("RWTimeout");
    this->userName = kvmap.GetString("UserName");
    this->password = kvmap.GetString("Password");

}

void MysqlDAO::Query(const string& sql, KVMap& record)
{

}
void MysqlDAO::Query(const string& sql, ObjectList<KVMap>& recordList)
{

}


}}
