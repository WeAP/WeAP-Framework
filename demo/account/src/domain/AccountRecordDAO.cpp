#include "AccountRecordDAO.h"
#include "StringUtil.h"
#include "DateTime.h"

using namespace WeAP::System;

AccountRecordDAO::AccountRecordDAO()
{
    this->dbName = "account_db";
    this->tableName = "account_record";
    this->tableFields = "accountRecordId, accountId, accountType, currencyType, balance, freezedBalance, status, remark, "
                        "opType, opAmount, opFreezedAmount, accountTransactionId, accountEvidenceId, "
                        "dataVersion, dataSign, createTime, modifyTime";
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
    if (accountRecord.createTime.empty() || accountRecord.modifyTime.empty())
    {
        string now = DateTime().ToDateTimeString();
        accountRecord.createTime = now;
        accountRecord.modifyTime = now;
    }

    if (accountRecord.dataSign.empty())
    {
        accountRecord.dataSign = accountRecord.GenDataSign();
    }

    Sql sql;
    sql.Append("insert");
    sql.Append(this->GetFullTableName(accountRecord.accountId));
    sql.Append("(");
    sql.Append(this->tableFields);
    sql.Append(") values (");
    sql.AppendValue(accountRecord.accountRecordId);
    sql.AppendValue(accountRecord.accountId);
    sql.AppendValue(accountRecord.accountType);    
    sql.AppendValue(accountRecord.currencyType );
    sql.AppendValue(accountRecord.balance );
    sql.AppendValue(accountRecord.freezedBalance);
    sql.AppendValue(accountRecord.status);
    sql.AppendValue(accountRecord.remark);
    sql.AppendValue(accountRecord.opType);
    sql.AppendValue(accountRecord.opAmount);
    sql.AppendValue(accountRecord.opFreezedAmount);
    sql.AppendValue(accountRecord.accountTransactionId);
    sql.AppendValue(accountRecord.accountEvidenceId);
    sql.AppendValue(accountRecord.dataVersion);
    sql.AppendValue(accountRecord.dataSign);
    sql.AppendValue(accountRecord.createTime);
    sql.AppendValue(accountRecord.modifyTime, true);
    sql.Append(")");

    MySQLDAO::Insert(sql.ToString(), transHandler);

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

void AccountRecordDAO::Query(uint64_t accountRecordId, AccountRecord& accountRecord)
{
    KVMap record;
    this->Query(accountRecordId, record);
    accountRecord = record;
}
void AccountRecordDAO::Query(uint64_t accountRecordId, KVMap& record)
{
    Sql sql;
    sql.Append("select");
    sql.Append(this->tableFields);
    sql.Append("from");
    sql.Append(this->GetFullTableName(accountRecordId));
    sql.Append("where");
    sql.AppendValue("accountRecordId", accountRecordId, true);

    MySQLDAO::Query(sql.ToString(), record);
}

