
#include "CronTask.h"
#include "Util.h"
 #include<sys/stat.h>

namespace WeAP { namespace Framework {


CronTask::CronTask()
{
}

CronTask::~CronTask()
{

}

void CronTask::Init(const string& confFile)
{
    INIConfig config;
    config.Init(confFile);

    this->DoInit(config);
}

void CronTask::CronTask::Execute()
{

    try
    {
        this->DoExecute();
    }
    catch(const Exception& ex)
    {
        ERROR("task execute failed, errorCode:%d, errorMessage:%s, taskName:%s", ex.errorCode, ex.errorMessage.c_str(), this->taskName.c_str());
    }
    catch(const std::exception& ex)
    {
        ERROR("task execute failed, std ex:%s, taskName:%s", ex.what(), this->taskName.c_str());
    }

}

}}
