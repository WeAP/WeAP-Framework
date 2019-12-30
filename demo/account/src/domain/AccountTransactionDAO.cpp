#include "AccountTransactionDAO.h"
#include "StringUtil.h"
#include "DateTime.h"

using namespace WeAP::System;

AccountTransactionDAO::AccountTransactionDAO()
{
    this->dbName = "account_db";
    this->tableName = "account_transaction";
    this->tableFields = "accountTransactionId, type, status, accountId, accountType, currencyType, amount, freezedAmount, remark,"
                        "dataVersion, dataSign, createTime, modifyTime";
}

AccountTransactionDAO::~AccountTransactionDAO()
{

}


void AccountTransactionDAO::Insert(AccountTransaction& accountTransaction, MySQLTransaction& trans)
{
    this->Insert(accountTransaction, trans.GetMySQL());
}

void AccountTransactionDAO::Insert(AccountTransaction& accountTransaction, MySQL* transHandler)
{
    if (accountTransaction.createTime.empty() || accountTransaction.modifyTime.empty())
    {
        string now = DateTime().ToDateTimeString();
        accountTransaction.createTime = now;
        accountTransaction.modifyTime = now;
    }

    if (accountTransaction.dataSign.empty())
    {
        accountTransaction.dataSign = accountTransaction.GenDataSign();
    }

    SQL sql;
    sql.Append("insert");
    sql.Append(this->GetFullTableName(accountTransaction.accountTransactionId));
    sql.Append("(");
    sql.Append(this->tableFields);
    sql.Append(") values (");
    sql.AppendValue(accountTransaction.accountTransactionId);
    sql.AppendValue(accountTransaction.type);
    sql.AppendValue(accountTransaction.status);
    sql.AppendValue(accountTransaction.accountId);
    sql.AppendValue(accountTransaction.accountType);
    sql.AppendValue(accountTransaction.currencyType);
    sql.AppendValue(accountTransaction.amount);
    sql.AppendValue(accountTransaction.freezedAmount);
    sql.AppendValue(accountTransaction.remark);
    sql.AppendValue(accountTransaction.dataVersion);
    sql.AppendValue(accountTransaction.dataSign);
    sql.AppendValue(accountTransaction.createTime);
    sql.AppendValue(accountTransaction.modifyTime, true);
    sql.Append(")");

    //MySQLDAO::Insert(sql.ToString(), transHandler);

}

void AccountTransactionDAO::Update(AccountTransaction& accountTransaction, MySQL* transHandler)
{
    accountTransaction.modifyTime = DateTime().ToDateTimeString();
    accountTransaction.dataSign = accountTransaction.GenDataSign();

    SQL sql;
    sql.Append("update");
    sql.Append(this->GetFullTableName(accountTransaction.accountTransactionId));
    sql.Append("set");
    sql.AppendValue("accountId", accountTransaction.accountId);
    sql.AppendValue("currencyType", accountTransaction.currencyType);
    sql.AppendValue("status", accountTransaction.status);
    sql.AppendValue("dataVersion", accountTransaction.dataVersion + 1);
    sql.AppendValue("dataSign", accountTransaction.dataSign);
    //sql.AppendValue("createTime", account.createTime);
    sql.AppendValue("modifyTime", accountTransaction.modifyTime, true);
    sql.Append("where");
    sql.AppendCond("accountTransactionId", accountTransaction.accountTransactionId);
    sql.AppendCond("dataVersion", accountTransaction.dataVersion, true);

    //INFO("sql:%s",sql.ToString().c_str());


    //MySQLDAO::Update(sql.ToString(), transHandler);

    accountTransaction.dataVersion += 1;

}

void AccountTransactionDAO::Query(uint64_t accountTransactionId, AccountTransaction& accountTransaction)
{
    KVMap record;
    this->Query(accountTransactionId, record);
    accountTransaction = record;
}

void AccountTransactionDAO::Query(uint64_t accountTransactionId, KVMap& record)
{
    SQL sql;
    sql.Append("select");
    sql.Append(this->tableFields);
    sql.Append("from");
    sql.Append(this->GetFullTableName(accountTransactionId));
    sql.Append("where");
    sql.AppendValue("accountTransactionId", accountTransactionId, true);

    MySQLDAO::Query(sql.ToString(), record);
    //cout << record.ToString() << endl;
}


