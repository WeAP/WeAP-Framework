#ifndef __WeAP_AccountManager_H__
#define __WeAP_AccountManager_H__

#include "Manager.h"
#include "Singleton.h"
#include "AccountDAO.h"
#include "AccountRecordDAO.h"
#include "AccountTransactionDAO.h"
#include "KeyGenerator.h"
#include "RedisDAO.h"

using namespace WeAP::Framework;
using namespace WeAP::Redis;


class AccountManager : public Manager
{
public:
    AccountManager();
    virtual ~AccountManager();

    void Init(const string& confFile);

public:
    AccountDAO accountDAO;
    AccountRecordDAO accountRecordDAO;
    AccountTransactionDAO accountTransactionDAO;
    KeyGenerator keyGenerator;
    RedisDAO redisDAO;
    

};

typedef Singleton<AccountManager> AccountManagerS;

#endif 
