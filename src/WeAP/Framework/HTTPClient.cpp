
#include "HTTPClient.h"



namespace WeAP { namespace Framework {



HTTPClient::HTTPClient()
{
}


HTTPClient::~HTTPClient()
{

}

void HTTPClient::Init(const INIConfig& config, const string& section)
{
    KVMap kvmap;
    config.GetSection(section, kvmap);
    this->ip = kvmap.GetString("IP");
    this->port = kvmap.GetUInt32("Port");
    this->connTimeoutMs = kvmap.GetUInt32("ConnTimeout");
    this->rwTimeoutMs = kvmap.GetUInt32("RWTimeout");

}

}}
