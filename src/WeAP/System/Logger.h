#ifndef __WeAP_Logger_H__
#define __WeAP_Logger_H__

#include "Singleton.h"
#include <glog/logging.h>
#include <string>
#include "StringUtil.h"
using namespace std;


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

    //void Init(const string& moduleName, const string& section);    
    void Init(const string& logDir, int logLevel, int logSize, const string& moduleName);


protected:
//    void SetLogPath()

};


#define ERROR(format, argv...)      \
do                                  \
{                                   \
    string str = StringUtil::Format(format, ##argv) ; \
    LOG(ERROR) << str;             \
}while(0)

#define WARN(format, argv...)      \
do                                  \
{                                   \
    string str = StringUtil::Format(format, ##argv) ; \
    LOG(WARNING) << str;             \
}while(0)

#define INFO(format, argv...)      \
do                                  \
{                                   \
    string str = StringUtil::Format(format, ##argv) ; \
    LOG(INFO) << str;             \
}while(0)

#define DEBUG(format, argv...)      \
do                                  \
{                                   \
    string str = StringUtil::Format(format, ##argv) ; \
    DLOG(INFO) << str;             \
}while(0)


#define GLOG  LOG(ERROR)



}}


#endif //__WeAP_Logger_H__
