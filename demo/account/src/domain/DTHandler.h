#ifndef __WeAP_DTHandler_H__
#define __WeAP_DTHandler_H__

#include "Handler.h"

using namespace WeAP::Framework;

class DTHandler : public Handler
{
public:
    DTHandler();
    virtual ~DTHandler();

    virtual void Prepare(){};

    virtual void Commit(){};

    virtual void Rollback(){};

    virtual void Finish(){};

};


#endif