#ifndef __WeAP_RPC_H__
#define __WeAP_RPC_H__

#include "Routine.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class RPC : public Routine
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

