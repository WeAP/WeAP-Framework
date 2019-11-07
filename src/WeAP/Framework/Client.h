#ifndef __WeAP_Client_H__
#define __WeAP_Client_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class Client : public AppObject
{
public:
    Client();
    virtual ~Client();

private:
    Client(const Client& other);
    Client& operator=(const Client& other);

protected:

};

}}


#endif //__WeAP_Client_H__

