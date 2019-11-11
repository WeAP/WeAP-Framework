#ifndef __WeAP_HTTPClient_H__
#define __WeAP_HTTPClient_H__

#include "Client.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class HTTPClient : public Client
{
public:
    HTTPClient();
    virtual ~HTTPClient();

    void Init(const INIConfig& config, const string& section);

private:
    HTTPClient(const HTTPClient& other);
    HTTPClient& operator=(const HTTPClient& other);

protected:
    string ip;
    uint32_t port;
    uint32_t connTimeoutMs;
    uint32_t rwTimeoutMs;
};

}}


#endif //__WeAP_HTTPClient_H__

