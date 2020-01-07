#ifndef __WeAP_AccountPlusHandler_H__
#define __WeAP_AccountPlusHandler_H__

#include "STHandler.h"

using namespace WeAP::Framework;

class AccountPlusHandler : public STHandler
{
public:
    AccountPlusHandler();
    virtual ~AccountPlusHandler();

    virtual void Prepare();

    virtual void Commit();

    virtual void Rollback();

    virtual void Finish();

};


#endif