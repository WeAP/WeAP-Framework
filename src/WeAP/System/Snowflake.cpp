#include "Snowflake.h"



namespace WeAP{ namespace System {



Snowflake::Snowflake()
{ 
}


Snowflake::~Snowflake()
{

}

void Snowflake::SetWorkerId(uint32_t workerId) 
{
    this->workerId = workerId;
}

void Snowflake::SetDataCenterId(uint32_t dataCenterId) 
{
    this->dataCenterId = dataCenterId;
}

uint64_t Snowflake::NextId64() 
{
    std::unique_lock<std::mutex> lock{ this->mutex };

    uint64_t timestamp = this->GetTimestamp();

    // 如果当前时间小于上一次ID生成的时间戳，说明系统时钟回退过这个时候应当抛出异常
    if (timestamp < lastTimestamp) 
    {
        std::ostringstream s;
        s << "clock moved backwards.  Refusing to generate id for " << lastTimestamp - timestamp << " milliseconds";
        throw std::exception(std::runtime_error(s.str()));
    }

    if (lastTimestamp == timestamp) 
    {
        // 如果是同一时间生成的，则进行毫秒内序列
        this->sequence = (this->sequence + 1) & this->SequenceMask;
        if (0 == this->sequence) 
        {
            // 毫秒内序列溢出, 阻塞到下一个毫秒,获得新的时间戳
            timestamp = this->WaitNextTimestamp(lastTimestamp);
        }
    } 
    else 
    {
        this->sequence = 0;
    }

    lastTimestamp = timestamp;


    //cout << "timestamp:" << timestamp << endl;
    //cout << "sequence:" << sequence << endl;

    // 移位并通过或运算拼到一起组成64位的ID
    return ((timestamp - this->StartTime) << this->TimestampLeftShift)
    | (this->dataCenterId << this->DatacenterIdShift)
    | (this->workerId << this->WorkerIdShift)
    | sequence;
}


uint64_t Snowflake::WaitNextTimestamp(uint64_t lastTimestamp) const 
{
    uint64_t timestamp = this->GetTimestamp();
    while (timestamp <= lastTimestamp) 
    {
        timestamp = this->GetTimestamp();
    }
    return timestamp;
}

uint64_t Snowflake::GetTimestamp() const 
{
    auto t = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
    return t.time_since_epoch().count();
}


}}
