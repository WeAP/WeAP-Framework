#include "AccountRecordDAO.h"
#include "StringUtil.h"

using namespace WeAP::System;

AccountRecordDAO::AccountRecordDAO()
{
}

AccountRecordDAO::~AccountRecordDAO()
{

}

void AccountRecordDAO::Insert(AccountRecord& accountRecord, MySQLTransaction& trans)
{
    this->Insert(accountRecord, trans.GetMySQL());
}


void AccountRecordDAO::Insert(AccountRecord& accountRecord, MySQL* transHandler)
{
    Sql sql;
    sql.Append("insert");
    sql.Append(this->GetFullTableName(accountRecord.accountId));
    sql.Append("(");
    sql.Append(this->tableFields);
    sql.Append(") values (");
    sql.AppendValue(accountRecord.accountId);
    sql.AppendValue(accountRecord.accountType);    
    sql.AppendValue(accountRecord.currencyType );
    sql.AppendValue(accountRecord.balance );
    sql.AppendValue(accountRecord.freezedBalance);
    sql.AppendValue(accountRecord.status);
    sql.AppendValue(accountRecord.dataVersion);
    sql.AppendValue(accountRecord.dataSign);
    sql.AppendValue(accountRecord.createTime);
    sql.AppendValue(accountRecord.modifyTime, true);
    sql.Append(")");

    //MySQLDAO::Insert(sql.ToString(), transHandler);

}

void AccountRecordDAO::Query(uint64_t accountId, AccountRecordList& list)
{
    Sql sql;
    sql.Append("select");
    sql.Append(this->tableFields);
    sql.Append("from");
    sql.Append(this->GetFullTableName(accountId));
    sql.Append("where");
    sql.AppendValue("accountId", accountId, true);

    ObjectList<KVMap> recordList;
    MySQLDAO::Query(sql.ToString(), recordList);
}
