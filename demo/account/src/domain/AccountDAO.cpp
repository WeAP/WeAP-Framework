#include "AccountDAO.h"
#include "StringUtil.h"
//#include "MySQL.h"

using namespace WeAP::System;

AccountDAO::AccountDAO()
{
    this->dbName = "account_db";
    this->tableName = "account";
    this->tableFields = "accountId, accountType, currencyType, balance, freezedAmount, status,"
                        "dataVersion, dataSign, createTime, modifyTime";
}

AccountDAO::~AccountDAO()
{

}

void AccountDAO::Insert(Account& account)
{
    Sql sql;
    sql.Append("insert");
    sql.Append(this->GetFullTableName());
    sql.Append("(");
    sql.Append(this->tableFields);
    sql.Append(") values (");
    sql.AppendValue(account.accountId);
    sql.AppendValue(account.accountType);    
    sql.AppendValue(account.currencyType );
    sql.AppendValue(account.balance );
    sql.AppendValue(account.freezedAmount);
    sql.AppendValue(account.status);
    sql.AppendValue(account.dataVersion);
    sql.AppendValue(account.dataSign);
    sql.AppendValue(account.createTime);
    sql.AppendValue(account.modifyTime, true);
    sql.Append(")");

    INFO("sql:%s",sql.ToString().c_str());
    MySQLDAO::Insert(sql.ToString());

}

void AccountDAO::Query(uint64_t accountId, Account& account)
{
    KVMap record;
    this->Query(accountId, record);
    account = record;
}

void AccountDAO::Query(uint64_t accountId, KVMap& record)
{
    Sql sql;
    sql.Append("select");
    sql.Append(this->tableFields);
    sql.Append("from");
    sql.Append(this->GetFullTableName());
    sql.Append("where");
    sql.AppendValue("accountId", accountId, true);

    MySQLDAO::Query(sql.ToString(), record);
    //cout << record.ToString() << endl;
}


void AccountDAO::Update(const Account& account)
{

    Sql sql;
    sql.Append("update");

    sql.Append(this->GetFullTableName());
    sql.Append("set");
    sql.AppendValue("accountId", account.accountId);
    sql.AppendValue("currencyType", account.currencyType);
    sql.AppendValue("balance", account.balance);
    sql.AppendValue("freezedAmount", account.freezedAmount);
    sql.AppendValue("status", account.status);
    sql.AppendValue("dataVersion", account.dataVersion + 1);
    sql.AppendValue("dataSign", account.GenDataSign());
    //sql.AppendValue("createTime", account.createTime);
    sql.AppendValue("modifyTime", account.modifyTime, true);
    sql.Append("where");
    sql.AppendCond("accountId", account.accountId);
    sql.AppendCond("dataVersion", account.dataVersion, true);

    INFO("sql:%s",sql.ToString().c_str());
    MySQLDAO::Update(sql.ToString());

}