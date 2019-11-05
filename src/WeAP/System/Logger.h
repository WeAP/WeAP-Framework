#ifndef __WeAP_Logger_H__
#define __WeAP_Logger_H__

#include "Singleton.h"

namespace WeAP { namespace System {

/**
 * print log to file
 * 
 * @author xzwang
 * @date 2018-05-10
 */
class Logger : public Singleton<Logger>
{
public:
    Logger();
    virtual ~Logger();

    virtual void Dump();


private:
    Logger(const Logger& other);
    Logger& operator=(const Logger& other);

    void Init(const Logger& other);

protected:
    virtual void Clear();

protected:

};



#define ERROR(format, argv...)  do {}while(0)
#define WARN(format, argv...)do {}while(0)
#define INFO(format, argv...) do {}while(0)
#define DEBUG(format, argv...)  do {}while(0)

}}


#endif //__WeAP_Logger_H__
