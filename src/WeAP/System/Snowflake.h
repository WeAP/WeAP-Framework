#ifndef __WeAP_Snowflake_H__
#define __WeAP_Snowflake_H__

#include "Object.h"
#include<chrono>
#include<mutex>

using namespace std;

namespace WeAP { namespace System {


/**
 * @brief 分布式id生成类
 * https://segmentfault.com/a/1190000011282426
 * https://github.com/twitter/snowflake/blob/snowflake-2010/src/main/scala/com/twitter/service/snowflake/IdWorker.scala
 *
 * 64bit id: 0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000 
 *           ||                                                           ||     ||     |  |              | 
 *           |└---------------------------时间戳--------------------------┘└中心--┘└机器-┘  └----序列号----┘ 
 *           |
 *         不用
 * SnowFlake的优点: 整体上按照时间自增排序, 并且整个分布式系统内不会产生ID碰撞(由数据中心ID和机器ID作区分), 并且效率较高, 经测试, SnowFlake每秒能够产生26万ID左右.
 *
 * 
 * 1位: 不用, 二进制中最高位为1的都是负数, 但是我们生成的id一般都使用整数, 所以这个最高位固定是0.

41位: 用来记录时间戳(毫秒级), 注意, 这里存储的不是当前的时间戳，而是存储时间戳的差值(当前时间截 - 开始时间截), 可以表示69年的时间.

10位: 用来记录工作机器id, 可以部署在1024个节点, 包括5位dataCenterId和5位workerId.

12位: 序列号，用来记录同毫秒内产生的不同id, 同一机器同一时间截（毫秒)内可以产生4096个序列号, 也就是1毫秒内可以产生4096个id.

 */
class Snowflake: public Object
{
protected:
    //开始时间截 (2018-01-01 00:00:00.000)    
    const uint64_t StartTime = 1514736000000;

    // 机器id所占的位数
    const uint32_t workerIdBits = 5;

    //数据中心id所占的位数
    const uint32_t DataCenterIdBits = 5;

    //序列所占的位数
    const uint32_t SequenceBits = 12;

    // 机器ID向左移12位
    const uint32_t WorkerIdShift = SequenceBits;

    //数据标识id向左移17位
    const uint32_t DatacenterIdShift = WorkerIdShift + workerIdBits;

    //时间截向左移22位
    const uint32_t TimestampLeftShift = DatacenterIdShift + DataCenterIdBits;

    //支持的最大机器id，结果是31
    const uint32_t MaxWorkerId = -1 ^ (-1 << workerIdBits);

    //支持的最大数据中心id，结果是31
    const uint32_t MaxDatacenterId = -1 ^ (-1 << DataCenterIdBits);

    // 生成序列的掩码，这里为4095
    const uint32_t SequenceMask = -1 ^ (-1 << SequenceBits);

public:
    Snowflake();
    virtual ~Snowflake();
    void SetWorkerId(uint32_t workerId);
    void SetDataCenterId(uint32_t dataCenterId);

    /**
     * 获得下一个ID (该方法是线程安全的)
     */
    uint64_t NextId64();

    /**
     * 阻塞到下一个毫秒，直到获得新的时间戳
     */
    uint64_t WaitNextTimestamp(uint64_t lastTimestamp) const;

    /**
     * 返回以毫秒为单位的当前时间
     */
    uint64_t GetTimestamp() const;

private:
    uint32_t workerId{0}; //工作机器id(0~31)    
    uint32_t dataCenterId{0}; // 数据中心id(0~31)    
    uint32_t sequence{ 0 }; //毫秒内序列(0~4095)    
    uint64_t lastTimestamp{ 0 }; // 上次生成ID的时间截

    std::mutex mutex;
};


}}

#endif //__WeAP_Snowflake_H__
