#include "BatchTask.h"
#include "Util.h"
 #include <sys/stat.h>
#include <wait.h>

namespace WeAP { namespace Framework {


BatchTask::BatchTask()
{
}

BatchTask::~BatchTask()
{

}

void BatchTask::DoExecute()
{
    this->MultiProcess();
}

void BatchTask::MultiProcess() 
{
    std::vector<std::pair<int, int>> vecTableRanges;
    this->GetTableRanges(this->tableCount, this->parallelCount, vecTableRanges);

    for (size_t i = 0; i < vecTableRanges.size(); i++)
    {
        if (fork() == 0)
        {
            std::pair<int, int> range = vecTableRanges[i];
            this->ProcessTables(range.first, range.second);
            exit(EXIT_SUCCESS);
        }
    }

    for (size_t i = 0; i < vecTableRanges.size(); i++) 
    {
        int status = -1;
        int pid = wait(&status);
        INFO("child process exit, pid:%d, status:%s", pid, status);
    }
}


void BatchTask::GetTableRanges(int iTotalCount, int iParallelCount , std::vector<std::pair<int, int>>& vecTableRanges)
{
    vecTableRanges.clear();
    if (iTotalCount <= 0 || iParallelCount <= 0  ) 
    {
        WARN("GetTableRanges iTotalCount: %d, iParallelCount: %d", iTotalCount, iParallelCount);
        return;
    }

    // 只有并行实例：处理所有数据
    if (iParallelCount == 1)
    {
        vecTableRanges.push_back(std::make_pair(0, iTotalCount));
        return;
    }

    // 并行数比数据总数多：最多总数个并行实例，每个实例分配1个任务
    if (iParallelCount >= iTotalCount)
    {
        for (int i = 0; i < iTotalCount; i++) 
        {
            vecTableRanges.push_back(std::make_pair(i, i+1));
        }
        return;
    }

    int iBaseDataCount = iTotalCount / iParallelCount;
    // 前iExtraCount个线程，每个多分配1个任务
    int iExtraCount = iTotalCount % iParallelCount;

    vecTableRanges.push_back(std::make_pair(0, iExtraCount > 0 ? iBaseDataCount + 1 : iBaseDataCount));
    for (int i = 1; i < iParallelCount; i++) 
    {
        std::pair<int, int> pairRange = vecTableRanges.back();
        int iCurrentSize = iExtraCount > i ? iBaseDataCount+1 : iBaseDataCount;
        vecTableRanges.push_back(std::make_pair(pairRange.second, pairRange.second + iCurrentSize));
    }
}


void BatchTask::ProcessTables(int iBeginIndex, int iEndIndex)
{
    int iFailedTable = 0;
    int iTotalTable = 0;
    int iTotalRecord = 0;
    
    for (int i = iBeginIndex; i < iEndIndex; i++)
    {
        iTotalTable ++;
        int iRecordCount = 0;
        this->ProcessTable(i, iRecordCount);

        iTotalRecord += iRecordCount;

        //if (iRecordCount > 0)
        //{
        //    PLOG_RUN_PASS_EX("ProcessTable", "iTableIndex:%d, iRecordCount:%d", i, iRecordCount);
        //}
        
    }

    INFO("ProcessTables, pid: %d, table range [%d, %d], iTotalTable: %d, iFailedTable: %d, iTotalRecord:%d",
                                        ::getpid(), iBeginIndex, iEndIndex, iTotalTable, iFailedTable,  iTotalRecord);

}

void BatchTask::ProcessTable(int32_t iTableIndex, int32_t& iRecordCount)
{
    int iOffset = 0;
    const int iLimit = 2000;
    int iCount;

    do 
    {
        ObjectList<KVMap> records;
        this->Query(iTableIndex, 0, time(NULL), iOffset, iLimit, records);

        iCount = records.GetCount();

        if (iCount > 0)
        {
            //INFO("Query, iTableIndex:%d, iCount:%d", iTableIndex, iCount);
            this->ProcessList(records);

            iOffset += iCount;
            iRecordCount += iCount;
        }

    } while (iCount == iLimit);

};

void BatchTask::ProcessList(const ObjectList<KVMap>& records)
{
    int count = records.GetCount();
    for (int i = 0; i < count; i++)
    {
        const KVMap* record = records.Get(i);

        this->CheckRecord(*record);

        this->ProcessRecord(*record);
    }
}

}}
