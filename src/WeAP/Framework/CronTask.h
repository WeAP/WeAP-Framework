#ifndef __WeAP_CronTask_H__
#define __WeAP_CronTask_H__

#include "Routine.h"
#include "INIConfig.h"

namespace WeAP { namespace Framework {

/**
 * a task for crontab
 * 
 * @author xzwang
 */
class CronTask: public Routine
{
public:
    CronTask();
    virtual ~CronTask();

    void Init(const string& confFile);
    void Execute(); 

protected:
    virtual void DoInit(const INIConfig& config) = 0;
    virtual void DoExecute() = 0;

private:
    CronTask(const CronTask& other);
    CronTask& operator=(const CronTask& other);
protected:
    string taskName;

};

}}


#endif //__WeAP_CronTask_H__

