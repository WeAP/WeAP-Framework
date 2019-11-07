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


private:
    HTTPClient(const HTTPClient& other);
    HTTPClient& operator=(const HTTPClient& other);

protected:

};

}}


#endif //__WeAP_HTTPClient_H__

