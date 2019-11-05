#ifndef __WeAP_HTTPClient_H__
#define __WeAP_HTTPClient_H__

#include "Client.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class HTTPClient : public Client
{
public:
    HTTPClient();
    virtual ~HTTPClient();

    virtual void Dump();


private:
    HTTPClient(const HTTPClient& other);
    HTTPClient& operator=(const HTTPClient& other);

    void Init(const HTTPClient& other);

protected:
    virtual void Clear();

protected:

};

}}


#endif //__WeAP_HTTPClient_H__

