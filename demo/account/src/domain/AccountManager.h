#ifndef __WeAP_AccountManager_H__
#define __WeAP_AccountManager_H__

#include "Manager.h"
#include "Singleton.h"
#include "AccountDAO.h"
#include "AccountRecordDAO.h"
#include "AccountTransactionDAO.h"


using namespace WeAP::Framework;


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

};

Singleton<AccountManager> AccountManagerS;

#endif 
