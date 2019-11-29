
#include "Daemon.h"
#include "Util.h"
 #include<sys/stat.h>

namespace WeAP { namespace Framework {


Daemon::Daemon()
{
    this->intervalType = Fixed;
    this->intervalSeconds = 0;   ///< 间隔时间(秒)
    this->minIntervalSeconds = 0;   ///< 间隔时间(秒)
    this->maxIntervalSeconds = 0;   ///< 间隔时间(秒)
    this->loopCount = 0;
}



Daemon::~Daemon()
{

}

void Daemon::Init(const string& confFile)
{

}
void Daemon::Init(IntervalType intervalType,
                  int intervalSeconds,
                  int minIntervalSeconds,
                  int maxIntervalSeconds)
{
    this->intervalType = intervalType;
    this->intervalSeconds = intervalSeconds;
    this->minIntervalSeconds = minIntervalSeconds;
    this->maxIntervalSeconds = maxIntervalSeconds;
}


void Daemon::Execute(bool nochdir/* = false*/, bool noclose/* = false*/)
 { 
    pid_t pid = ::fork();
    if (pid < 0)
    {
        //perror(pid);
        ERROR("fork failed. pid:%d", pid);
        exit(-1);
    }
    else if (pid > 0 ) 
    {
        INFO("the parent process exit, pid: %d", ::getpid());
        exit(0);
    }
    else if(pid == 0)
    {
        //this->pid = ::getpid();
        INFO("the child process is running, pid: %d", ::getpid() );
    }
    
    pid_t sid = ::setsid(); 
    if (sid < 0)
    {         
        ERROR("::setsid failed. ret:%d, pid:%d", ::getpid(), (int)sid);
        exit(-1);
    }
    
    int ret = ::chdir("/");
    if (ret < 0)
    {
        ERROR("chdir", ret,"::chdir failed. ret:%d, pid:%d", ret, ::getpid());
        exit(-1);
    }
    
    /*
    int fd = ::open("/dev/null", O_RDWR, 0);
    if(fd != -1)
    {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
    if(fd > 2)
    {
        ::close(fd);
    }
    }
    */
    
    ::close(STDIN_FILENO);
    ::close(STDOUT_FILENO);
    ::close(STDERR_FILENO);
    
    ::umask(0);
    
    while (1)
    {
        
        try
        {
            INFO("DoExecute loopCount: %d", this->loopCount);
            this->DoExecute();
        }
        catch(const Exception& ex)
        {
            ERROR("daemon execute failed. errorCode:%d, errorMessage:%s, DaemonName:%s", ex.errorCode, ex.errorMessage.c_str(), this->daemonName.c_str());
        }
        catch(const std::exception& ex)
        {
            ERROR("daemon execute failed. std ex:%s, DaemonName:%s", ex.what(), this->daemonName.c_str());
        }

        this->loopCount++;
    };
 
  };

void Daemon::Sleep()
{
    if (this->intervalType == Random)
    {
        this->intervalSeconds = Util::GetRandom(this->minIntervalSeconds, this->maxIntervalSeconds);
        INFO("random sleep %ds", this->intervalSeconds);
    }
    else
    {
        INFO("fixed sleep %ds", this->intervalSeconds);
    }
    

    if (this->intervalSeconds < 1)
    {
        return;
    }
    int usec = this->intervalSeconds * 1000000;
    ::usleep(usec);
}


}}
