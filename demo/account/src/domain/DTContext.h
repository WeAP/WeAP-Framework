#ifndef __WeAP_DTContext_H__
#define __WeAP_DTContext_H__

#include "Entity.h"

using namespace WeAP::Framework;

class DTContext : public Entity
{
public:
    enum DTStep
    {
        DTPrepare  = 1,
        DTCommit   = 2,
        DTRollback = 3,
        DTFinish   = 4,
    };
public:
    DTContext();
    virtual ~DTContext();

public:
    string txnNO;
    string cmd;
    KVMap params;
    string dtNO;
    int32_t currentStep;
    string lastTime;
    int32_t stNum;

};


#endif