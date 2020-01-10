#ifndef __WeAP_STHandler_H__
#define __WeAP_STHandler_H__

#include "Handler.h"
#include "STContext.h"
#include "AccountManager.h"
#include "MySQLTransaction.h"

using namespace WeAP::Framework;

class STHandler : public Handler
{
public:
    STHandler();
    virtual ~STHandler();

    virtual void Prepare(){};

    virtual void Commit(){};

    virtual void Rollback(){};

    virtual void Finish(){};

protected:
    virtual bool HasCommitted(){ return false; };

protected:
    STContext* stContext;
    AccountManager* manger;
};


#endif