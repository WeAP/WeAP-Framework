
#ifndef __WeAP_MySQLResult_H__
#define __WeAP_MySQLResult_H__

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
#include "ObjectList.h"

using namespace std;
using namespace WeAP::System;

namespace WeAP { namespace MySQL {


class MySQLResult
{
public:
    MySQLResult();
    virtual ~MySQLResult();

    void Init(MYSQL_RES* res);

    MySQLResult& operator=(MYSQL_RES* res);

    void To(KVMap& record, bool removePrefixF = false);
    void To(ObjectList<KVMap>& recordList, bool removePrefixF = false);

    int GetRowsNum();
    int GetFieldsNum();

protected:
    MYSQL_RES* res;
};


}}

#endif

