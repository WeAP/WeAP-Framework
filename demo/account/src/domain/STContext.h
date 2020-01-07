#ifndef __WeAP_STContext_H__
#define __WeAP_STContext_H__

#include "Entity.h"

using namespace WeAP::Framework;

class STContext : public Entity
{
public:
    STContext();
    virtual ~STContext();

    string txnNO;
    string dtcmd;
    string dtNO;
    KVMap params;

    int32_t stNum;
    string stcmd;
    int32_t stNO;
    string lastTime;
    
};


#endif