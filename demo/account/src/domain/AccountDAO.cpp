#include "AccountDAO.h"
#include "StringUtil.h"

using namespace WeAP::System;

AccountDAO::AccountDAO()
{
}

AccountDAO::~AccountDAO()
{

}

void AccountDAO::Insert(Account& account)
{
    string sql = StringUtil::Format("insert into account_db.account    \
                                    (accountId, amount, status, createTime, modifyTime) \
                                     values \
                                    (%llu, %u, %lld, now(), now())", 
                                    account.accountId, account.currencyType, account.balance);
    MySQLDAO::Insert(sql);

}

void AccountDAO::Query(uint64_t accountId, Account& account)
{
    string sql = "select * from account_db.account";
    KVMap record;
    MySQLDAO::Query(sql, record);
    
}
