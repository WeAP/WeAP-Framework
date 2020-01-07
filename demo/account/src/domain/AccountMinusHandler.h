#ifndef __WeAP_AccountMinusHandler_H__
#define __WeAP_AccountMinusHandler_H__

#include "STHandler.h"

using namespace WeAP::Framework;

class AccountMinusHandler : public STHandler
{
public:
    AccountMinusHandler();
    virtual ~AccountMinusHandler();

    virtual void Prepare();

    virtual void Commit();

    virtual void Rollback();

    virtual void Finish();

};


#endif