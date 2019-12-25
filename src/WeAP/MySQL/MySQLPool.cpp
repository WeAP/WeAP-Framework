#include "MySQLPool.h"
#include "Convert.h"

namespace WeAP { namespace MySQL {


MySQLPool::MySQLPool()
{

}

MySQLPool::~MySQLPool()
{
    for(map<string, MySQL*>::iterator it = this->pool.begin(); it != this->pool.end(); ++it)
    {
        if (it->second != NULL)
        {
            delete it->second;
            it->second = NULL;
        }
    }
}


CMySQL* MySQLPool::Add(const std::string& host,
                        int port,
                        const std::string& user, 
                        const std::string& passwd, 
                        int waitTimeoutS, 
                        int connTimeoutS,
                        int rwTimeoutS,
                        const std::string& charset, 
                        const std::string& dbName)
{
    string key = host + Convert::ToString(port) + user;

    map<string, MySQL*>::iterator it = this->pool.find(key);
    if ( it != this->pool.end())
    {
        return it->second;
    }

    this->connMap[key] = new MySQL();
    this->connMap[key]->Init(host, port, user,  passwd, waitTimeoutS, connTimeoutS, rwTimeoutS, charset, dbName)

    return this->connMap[key];
}





}}