#ifndef __WeAP_DTHandler_H__
#define __WeAP_DTHandler_H__

#include "Handler.h"
#include "DTContext.h"

using namespace WeAP::Framework;

class DTHandler : public Handler
{
public:
    DTHandler();
    virtual ~DTHandler();

    void Parse(const string& params);

    virtual void Prepare(){};

    virtual void Commit(){};

    virtual void Rollback(){};

    virtual void Finish(){};

protected:
    DTContext dtContext;
    string dtCMD;
};


#endif