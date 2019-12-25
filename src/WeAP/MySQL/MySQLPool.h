
#ifndef __WeAP_MySQLPool_H__
#define __WeAP_MySQLPool_H__


#include "Error.h"
#include "Exception.h"
#include "KVMap.h"
#include "MySQL.h"

using namespace std;

namespace WeAP { namespace MySQL {


/**
 *
 */
class MySQLPool
{
public:
    MySQLPool();    
    virtual ~MySQLPool();

    CMySQL* Add(const std::string& host,
                int port,
                const std::string& user, 
                const std::string& passwd, 
                int waitTimeoutS, 
                int connTimeoutS = 5,
                int rwTimeoutS = 5,
                const std::string& charset = "utf8", 
                const std::string& dbName = "");

protected:
    map<string, MySQL*> pool;
};



}}