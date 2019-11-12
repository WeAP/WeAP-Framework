#include "MySQLResult.h"
#include <sys/time.h>
#include "Logger.h"

namespace WeAP { namespace MySQL {

MySQLResult::MySQLResult()
{
    this->res = NULL;
}

MySQLResult::~MySQLResult()
{
    if (this->res != NULL)
    {
        mysql_free_result(this->res);
        this->res = NULL;
    }
}

void MySQLResult::Init(MYSQL_RES* res)
{
    this->res = res;
}

MySQLResult& MySQLResult::operator=(MYSQL_RES* res) 
{
    this->res = res;
    return *this;
}

void MySQLResult::To(KVMap& record, bool removePrefixF)
{
    int rowsNum = this->GetRowsNum();
    if(rowsNum == 0)
    {
        ERROR("mysql_num_rows is zero");
        throw Exception(Error::MySQL_Query_Rows_Not_One, "mysql_num_rows is zero");
    }
    else if(rowsNum != 1)
    {
        ERROR("mysql_num_rows is not one, rows: %d", rowsNum);
        throw Exception(Error::MySQL_Query_Rows_Not_One, "mysql_num_rows is not one");
    }

    //unsigned long* lengths = mysql_fetch_lengths(res);  //for binary
    
    MYSQL_ROW row = mysql_fetch_row(this->res);
    MYSQL_FIELD* field = mysql_fetch_fields(this->res);

    int fieldsNum = this->GetFieldsNum();
    for(int i = 0; i < fieldsNum; i++)
    {
        string fieldName = field[i].name;
        if (removePrefixF)
        {
            fieldName.substr(1);
        }

        string value = row[i] == NULL ? "": row[i];

        record.Set(fieldName, value);
    }
}

void MySQLResult::To(ObjectList<KVMap>& recordList, bool removePrefixF)
{
    MYSQL_FIELD* field = mysql_fetch_fields(this->res);
    int fieldsNum = this->GetFieldsNum();

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(this->res)))
    {
        for(int i = 0; i < fieldsNum; i++)
        {
            string fieldName = field[i].name;
            if (removePrefixF)
            {
                fieldName.substr(1);
            }
            string value = row[i] == NULL ? "": row[i];

            KVMap* record = recordList.Add();
            record->Set(fieldName, value);
        }
    }
}

int MySQLResult::GetRowsNum()
{
    return mysql_num_rows(this->res);
}

int MySQLResult::GetFieldsNum()
{
    return mysql_num_fields(this->res);
}

}}