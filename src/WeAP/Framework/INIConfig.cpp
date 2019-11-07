
#include "INIConfig.h"
#include "Util.h"
 #include<sys/stat.h>

namespace WeAP { namespace Framework {


INIConfig::INIConfig()
{
}



INIConfig::~INIConfig()
{

}

void INIConfig::Init(const string& confFile)
{
    this->confFile = confFile;
}


}}
