#ifndef __WeAP_RPC_H__
#define __WeAP_RPC_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class RPC : public AppObject
{
public:
    RPC();
    virtual ~RPC();

private:
    RPC(const RPC& other);
    RPC& operator=(const RPC& other);

};

}}


#endif //__WeAP_RPC_H__

