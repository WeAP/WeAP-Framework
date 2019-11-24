#include "Logger.h"
#include "FileUtil.h"

namespace WeAP { namespace System {


//将信息输出到单独的文件和 LOG(ERROR)
void SignalHandle(const char* data, int size)
{
    std::string str = std::string(data,size);

    string dumpFile = "";
    FileUtil::Dump(str, dumpFile);

    LOG(ERROR)<<str;
    //也可以直接在这里发送邮件或短信通知，不过这个方法是被回调多次的（每次回调只输出一行错误信息，所以如上面的记录到文件，也需要>以追加模式方可），所以这里发邮件或短信不是很适合，不过倒是可以调用一个 SHELL 或 PYTHON 脚本，而此脚本会先 sleep 3秒左右，然后将错误信息通过邮件或短信发送出去，这样就不需要监控脚本定时高频率执行，浪费效率了。
}


Logger::Logger()
{
}


Logger::~Logger()
{
    google::ShutdownGoogleLogging();
}

void Init(const string& moduleName,const string& section)
{

    string logDir = "";
    string logPrefix = moduleName.c_str();
    int logLevel = 1;
    int logSize = 100;

    if (!FileUtil::ExistDir(logDir))
    {
        FileUtil::MakeDir(logDir);
    }


    google::InitGoogleLogging(moduleName.c_str());
    FLAGS_stderrthreshold=google::INFO;
    FLAGS_v = 3;

    //google::SetStderrLogging(google::INFO); //设置级别高于 google::INFO 的日志同时输出到屏幕
    FLAGS_colorlogtostderr=true;    //设置输出到屏幕的日志显示相应颜色

    //设置 log 级别的日志存储路径和文件名前缀
    string logPath;
    switch (logLevel)
    {
    case 1:
        logPath = logDir + "/DEBUG_";
        //google::SetLogDestination(google::INFO,LOGDIR"/INFO_");
        google::SetLogFilenameExtension("91_");     //设置文件名扩展，如平台？或其它需要区分的信息
        break;
    case 2:
        logPath = logDir + "/INFO_";
        google::SetLogDestination(google::INFO, logPath.c_str());
        google::SetLogFilenameExtension("91_");     //设置文件名扩展，如平台？或其它需要区分的信息
        break;
    case 3:
        logPath = logDir + "/WARNING_";
        google::SetLogDestination(google::WARNING,logPath.c_str());
        google::SetLogFilenameExtension("91_");     //设置文件名扩展，如平台？或其它需要区分的信息
        break;
    case 4:
        logPath = logDir + "/ERROR_";
        google::SetLogDestination(google::ERROR,logPath.c_str());
        google::SetLogFilenameExtension("91_");     //设置文件名扩展，如平台？或其它需要区分的信息
        break;
    default:
        break;
    }

    FLAGS_logbufsecs =0;        //缓冲日志输出，默认为30秒，此处改为立即输出
    FLAGS_max_log_size = logSize;  //最大日志大小为 100MB
    FLAGS_stop_logging_if_full_disk = true;     //当磁盘被写满时，停止日志输出
    
    google::InstallFailureSignalHandler();      //捕捉 core dumped
    google::InstallFailureWriter(&SignalHandle);    //默认捕捉 SIGSEGV 信号信息输出会输出到 stderr，可以通过下面的方法自定义输出>方式：

}









}}
