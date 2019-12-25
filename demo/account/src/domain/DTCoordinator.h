#ifndef __WeAP_DTCoordinator_H__
#define __WeAP_DTCoordinator_H__


#include "Handler.h"


class DTCoordinator : public Handler
{
public:
    DTCoordinator();
    virtual ~DTCoordinator();

    virtual void Prepare(){};

    virtual void Commit(){};

    virtual void Rollback(){};

    virtual void Finish(){};

};

#endif