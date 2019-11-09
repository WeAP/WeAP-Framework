
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
    string ip = kvmap.GetString("IP");
    uint32_t port = kvmap.GetInt32("Port");
    uint32_t connTimeoutMs = kvmap.GetInt32("ConnTimeout");
    uint32_t RWTimeoutMs = kvmap.GetInt32("RWTimeout");

}

}}
