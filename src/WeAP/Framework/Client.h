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

    virtual void Dump();


private:
    Client(const Client& other);
    Client& operator=(const Client& other);

    void Init(const Client& other);

protected:
    virtual void Clear();

protected:

};

}}


#endif //__WeAP_Client_H__

