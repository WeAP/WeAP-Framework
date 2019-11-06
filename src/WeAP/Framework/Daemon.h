#ifndef __WeAP_Daemon_H__
#define __WeAP_Daemon_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class Daemon : public AppObject
{
public:
    enum IntervalType
    {
        Fixed = 1,  ///< 固定时间的
        Random = 2, ///< 在一定范围内随机
    };

public:
    Daemon();
    virtual ~Daemon();

    void Init(IntervalType intervalType,
              int intervalSeconds,
              int minIntervalSeconds,
              int maxIntervalSeconds);

    virtual void Dump();

    void Execute(bool nochdir = false, bool noclose = false); //常驻进程，不退出

protected:
    virtual int DoExecute() = 0;
    void Sleep();
    virtual void Clear();

private:
    Daemon(const Daemon& other);
    Daemon& operator=(const Daemon& other);

    void Init(const Daemon& other);

protected:
    IntervalType intervalType;
    int intervalSeconds;   ///< 间隔时间(秒)
    int minIntervalSeconds;   ///< 间隔时间(秒)
    int maxIntervalSeconds;   ///< 间隔时间(秒)

    int loopCount;
};

}}


#endif //__WeAP_Daemon_H__
