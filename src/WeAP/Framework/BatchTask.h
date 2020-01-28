#ifndef __WeAP_BatchTask_H__
#define __WeAP_BatchTask_H__

#include "CronTask.h"
#include "INIConfig.h"

namespace WeAP { namespace Framework {

/**
 * a task for crontab
 * 
 * @author xzwang
 */
class BatchTask: public CronTask
{
public:
    BatchTask();
    virtual ~BatchTask();

protected:
    virtual void DoInit(const INIConfig& config) = 0;
    virtual void DoExecute() = 0;

    virtual void CheckRecord();
    virtual void ProcessRecord();

private:
    BatchTask(const BatchTask& other);
    BatchTask& operator=(const BatchTask& other);


};

}}


#endif //__WeAP_BatchTask_H__

