#include "AccountTransactionDAO.h"
#include "StringUtil.h"

using namespace WeAP::System;

AccountTransactionDAO::AccountTransactionDAO()
{
}

AccountTransactionDAO::~AccountTransactionDAO()
{

}

void AccountTransactionDAO::Insert(AccountTransaction& txn)
{
    string sql = StringUtil::Format("insert into account_db.account    \
                                    (accountId, amount, status, createTime, modifyTime) \
                                     values \
                                    (%llu, %u, %lld, now(), now())", 
                                    txn.accountId, txn.currencyType, txn.balance);
    MySQLDAO::Insert(sql, NULL);

}

void AccountTransactionDAO::Query(uint64_t accountId, AccountTransaction& txn)
{
    string sql = "select * from account_db.account";
    KVMap record;
    MySQLDAO::Query(sql, record);
    
}
