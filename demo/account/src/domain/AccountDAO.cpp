#include "AccountDAO.h"
#include "StringUtil.h"
#include "DateTime.h"

using namespace WeAP::System;

AccountDAO::AccountDAO()
{
    this->dbName = "account_db";
    this->tableName = "account";
    this->tableFields = "accountId, accountType, currencyType, balance, freezedBalance, status, remark,"
                        "dataVersion, dataSign, createTime, modifyTime";
}

AccountDAO::~AccountDAO()
{

}

void AccountDAO::Insert(Account& account, MySQLTransaction& trans)
{
    this->Insert(account, trans.GetMySQL());
}

void AccountDAO::Insert(Account& account, MySQL* transHandler)
{
    if (account.createTime.empty() || account.modifyTime.empty())
    {
        string now = DateTime().ToDateTimeString();
        account.createTime = now;
        account.modifyTime = now;
    }

    if (account.dataSign.empty())
    {
        account.dataSign = account.GenDataSign();
    }

    Sql sql;
    sql.Append("insert");
    sql.Append(this->GetFullTableName(account.accountId));
    sql.Append("(");
    sql.Append(this->tableFields);
    sql.Append(") values (");
    sql.AppendValue(account.accountId);
    sql.AppendValue(account.accountType);    
    sql.AppendValue(account.currencyType );
    sql.AppendValue(account.balance );
    sql.AppendValue(account.freezedBalance);
    sql.AppendValue(account.status);
    sql.AppendValue(account.remark);
    sql.AppendValue(account.dataVersion);
    sql.AppendValue(account.dataSign);
    sql.AppendValue(account.createTime);
    sql.AppendValue(account.modifyTime, true);
    sql.Append(")");

    //INFO("sql:%s",sql.ToString().c_str());
    MySQLDAO::Insert(sql.ToString(), transHandler);

}

void AccountDAO::Update(Account& account, MySQLTransaction& trans)
{
    this->Update(account, trans.GetMySQL());
}

void AccountDAO::Update(Account& account, MySQL* transHandler)
{
    account.modifyTime = DateTime().ToDateTimeString();
    account.dataSign = account.GenDataSign();

    Sql sql;
    sql.Append("update");
    sql.Append(this->GetFullTableName(account.accountId));
    sql.Append("set");
    sql.AppendValue("accountId", account.accountId);
    sql.AppendValue("currencyType", account.currencyType);
    sql.AppendValue("balance", account.balance);
    sql.AppendValue("freezedBalance", account.freezedBalance);
    sql.AppendValue("status", account.status);
    sql.AppendValue("remark", account.remark);
    sql.AppendValue("dataVersion", account.dataVersion + 1);
    sql.AppendValue("dataSign", account.dataSign);
    //sql.AppendValue("createTime", account.createTime);
    sql.AppendValue("modifyTime", account.modifyTime, true);
    sql.Append("where");
    sql.AppendCond("accountId", account.accountId);
    sql.AppendCond("dataVersion", account.dataVersion, true);

    //INFO("sql:%s",sql.ToString().c_str());


    MySQLDAO::Update(sql.ToString(), transHandler);

    account.dataVersion += 1;

}

void AccountDAO::Query(uint64_t accountId, Account& account, MySQLTransaction& trans)
{
    this->Query(accountId, account, trans.GetMySQL());
}

void AccountDAO::Query(uint64_t accountId, Account& account, MySQL* transHandler)
{
    KVMap record;
    this->Query(accountId, record);
    account = record;
}

void AccountDAO::Query(uint64_t accountId, KVMap& record, MySQL* transHandler)
{
    Sql sql;
    sql.Append("select");
    sql.Append(this->tableFields);
    sql.Append("from");
    sql.Append(this->GetFullTableName(accountId));
    sql.Append("where");
    sql.AppendValue("accountId", accountId, true);
    if (transHandler != NULL)
    {
        sql.Append("for update");
    }

    MySQLDAO::Query(sql.ToString(), record);
    //cout << record.ToString() << endl;
}


