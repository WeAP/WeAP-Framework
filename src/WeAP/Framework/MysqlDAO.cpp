
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
    string ip = kvmap.GetString("IP");
    uint32_t port = kvmap.GetInt32("Port");
    uint32_t connTimeoutMs = kvmap.GetInt32("ConnTimeout");
    uint32_t RWTimeoutMs = kvmap.GetInt32("RWTimeout");
    string userName = kvmap.GetString("UserName");
    string password = kvmap.GetString("Password");

}


}}
