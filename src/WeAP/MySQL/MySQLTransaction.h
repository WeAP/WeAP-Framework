
#ifndef __WeAP_MySQLTransaction_H__
#define __WeAP_MySQLTransaction_H__


#include "MySQL.h"

using namespace std;

namespace WeAP { namespace MySQL {




/**
 *
 * 
 */
class MySQLTransaction
{
public:
    enum Status
    {
        NotBegin = 0,
        Began = 1,
        Committed = 2,
        Rollbacked = 3

    };

public:
    MySQLTransaction(MySQL* mysql);
    virtual ~MySQLTransaction();

    void Begin();
    void Commit();

    MySQL* GetMySQL();

protected:
    MySQL* mysql;
    Status status;
};

}}

#endif

