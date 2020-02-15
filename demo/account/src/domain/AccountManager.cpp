#include "AccountManager.h"
#include "INIConfig.h"

using namespace WeAP::System;

AccountManager::AccountManager()
{
}

AccountManager::~AccountManager()
{
}

void AccountManager::Init(const string& confFile)
{
    INIConfig config;
    config.Init(confFile);

    //const KVMap& logSection = config.GetSection("Log");

    string logDir = "/home/xzwang/WeAP-Framework/demo/account/log";
    //string logDir = logSection.GetString("LogDir");
    int logLevel = 1; //logSection.GetInt32("LogLevel");
    int logSize = 10; //logSection.GetInt32("LogSize");

    Logger::GetInstance()->Init(logDir, logLevel, logSize, "WeAP");

    this->accountDAO.Init(config, "Account");
    //this->accountRecordDAO.Init(config, "T_AccountRecord");
    //this->accountTransactionDAO.Init(config, "T_AccountTransaction");

    this->redisDAO.Init(config, "Redis");
}