#include "Logger.h"
#include <glog/logging.h>
#include <glog/log_severity.h> 
#include "FileUtil.h"
#include "AutoBuffer.h"
#include <stdarg.h>

namespace WeAP { namespace System {


//将信息输出到单独的文件和 LOG(ERROR)
void SignalHandle(const char* data, int size)
{
    std::string str = std::string(data,size);

    //string dumpFile = "";
    //FileUtil::Dump(str, dumpFile);

    LOG(ERROR)<< "SignalHandle:" << str;
    //也可以直接在这里发送邮件或短信通知，不过这个方法是被回调多次的（每次回调只输出一行错误信息，所以如上面的记录到文件，也需要>以追加模式方可），所以这里发邮件或短信不是很适合，不过倒是可以调用一个 SHELL 或 PYTHON 脚本，而此脚本会先 sleep 3秒左右，然后将错误信息通过邮件或短信发送出去，这样就不需要监控脚本定时高频率执行，浪费效率了。
}


Logger::Logger()
{
}


Logger::~Logger()
{
    google::ShutdownGoogleLogging();
}

/*
void Logger::Init(const string& moduleName, const string& section)
{

}
*/

void Logger::Init(const string& logDir, int logLevel, int logSize, const string& moduleName)
{
    string logPrefix = moduleName.c_str();

    if (!FileUtil::ExistDir(logDir))
    {
        FileUtil::MakeDir(logDir);
    }


    //SeverityLevel glogLever = google::INFO;
    int glogLever = 2;//google::INFO;
    string extName;

    //设置 log 级别的日志存储路径和文件名前缀
    string logPath;
    switch (logLevel)
    {
    case Debug:
        //glogLever = google::INFO;
        glogLever = 0;
        logPath = logDir + "/" +moduleName + ".DEBUG.";
        //extName = ".debug";
        break;
    case Info:
        //glogLever = google::INFO;
        glogLever = 0;
        logPath = logDir  + "/" +moduleName + ".INFO.";
        //extName = ".debug";
        break;
    case Warning:
        //glogLever = google::WARNING;
        glogLever = 1;
        logPath = logDir  + "/" +moduleName+ ".WARNING.";

        break;
    case Error:
        glogLever = 2;
        logPath = logDir  + "/" +moduleName + ".ERROR.";
        //glogLever = google::ERROR;

        break;

    case Fatal:
        glogLever = 3;
        logPath = logDir  + "/" +moduleName + ".ERROR.";
        //glogLever = google::FATAL;

        break;
    default:
        //throw Exception();
        break;
    }

    google::InitGoogleLogging(moduleName.c_str());
    FLAGS_max_log_size = logSize;  //最大日志大小为 100MB

    google::SetLogDestination(glogLever, logPath.c_str());
    google::SetLogFilenameExtension(extName.c_str());     //设置文件名扩展，如平台？或其它需要区分的信息

    //FLAGS_stderrthreshold = google::FATAL;
    //google::SetStderrLogging(google::FATAL); //设置级别高于 的日志同时输出到屏幕
    FLAGS_v = 3;


    FLAGS_logtostderr = false; // 是否将日志输出到stderr而非文件。
    FLAGS_alsologtostderr = false; //是否将日志输出到文件和stderr，如果：true，忽略FLAGS_stderrthreshold的限制，所有信息打印到终端。

    FLAGS_log_prefix = true; //设置日志前缀是否应该添加到每行输出。
    
    FLAGS_colorlogtostderr = true;    //设置输出到屏幕的日志显示相应颜色
    FLAGS_logbufsecs =0;        //缓冲日志输出，默认为30秒，此处改为立即输出
    FLAGS_stop_logging_if_full_disk = true;     //当磁盘被写满时，停止日志输出
    
    google::InstallFailureSignalHandler();      //捕捉 core dumped
    google::InstallFailureWriter(&SignalHandle);    //默认捕捉 SIGSEGV 信号信息输出会输出到 stderr，可以通过下面的方法自定义输出>方式：

}

void Logger::Write(LogLevel logLevel, const char* format, ...)
{
    if (format == NULL)
    {
        return;
    }

    va_list va;

    va_start(va, format);
    size_t len = vsnprintf(NULL, 0, format, va);
    va_end(va);

    if (len <= 0)
    {
        return;
    }

    va_list va2;
    va_start(va2, format);

    AutoBuffer buff(len);
    vsnprintf(buff.Get(), len + 1, format, va2);
    va_end(va2);

    string str = buff.ToString();

    switch (logLevel)
    {
    case Debug:
        DLOG(INFO) << str;
        break;
    case Info:
        LOG(INFO) << str;
        break;
    case Warning:
        LOG(WARNING) << str;
        break;
    case Error:
        LOG(ERROR) << str;
        break;

    case Fatal:
        LOG(FATAL) << str;
        break;
    default:
        break;
    }
    
}


}}
