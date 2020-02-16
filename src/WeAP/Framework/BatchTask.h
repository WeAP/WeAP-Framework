#ifndef __WeAP_BatchTask_H__
#define __WeAP_BatchTask_H__

#include "CronTask.h"
#include "INIConfig.h"
#include "ObjectList.h"

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
    virtual void DoExecute();

    virtual void CheckRecord(const KVMap& record) = 0;
    virtual void ProcessRecord(const KVMap& record) = 0;

    virtual void Query(int32_t iTableIndex,
                    time_t tBeginTime, 
                    time_t tEndTime, 
                    int iOffset, 
                    int iLimit, 
                    ObjectList<KVMap>& records) = 0;

    void MultiProcess();
    void GetTableRanges(int iTotalCount, int iParallelCount , std::vector<std::pair<int, int>>& vecTableRanges);
    void ProcessTables(int iBeginIndex, int iEndIndex);
    void ProcessTable(int32_t iTableIndex, int32_t& iRecordCount);
    void ProcessList(const ObjectList<KVMap>& records);

private:
    BatchTask(const BatchTask& other);
    BatchTask& operator=(const BatchTask& other);

protected:
    int tableCount {1024};
    int parallelCount {1};  //

};

}}


#endif //__WeAP_BatchTask_H__

