#include "AccountRecordDAO.h"
#include "StringUtil.h"

using namespace WeAP::System;

AccountRecordDAO::AccountRecordDAO()
{
}

AccountRecordDAO::~AccountRecordDAO()
{

}

void AccountRecordDAO::Insert(Account& account)
{
    stringstream sql;

    sql << "insert into account_db.account ";
    sql << "(accountId, currencyType, balance, freezedAmount, status, ";
    sql << "dataVersion, dataSign, createTime, modifyTime)";
    sql << "values (";
    sql << account.accountId << account.currencyType << account.balance << account.freezedAmount << account.status;
    sql << account.dataVersion << account.dataSign << account.createTime << account.modifyTime << ")";

    ERROR("sql:",sql.str().c_str());
    MySQLDAO::Insert(sql.str(), NULL);

}

void AccountRecordDAO::Query(uint64_t accountId, Account& account)
{
    string sql = "select * from account_db.account";
    KVMap record;
    MySQLDAO::Query(sql, record);
    
}
