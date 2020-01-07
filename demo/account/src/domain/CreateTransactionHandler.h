#ifndef __WeAP_CreateTransactionHandler_H__
#define __WeAP_CreateTransactionHandler_H__

#include "STHandler.h"

using namespace WeAP::Framework;

class CreateTransactionHandler : public STHandler
{
public:
    CreateTransactionHandler();
    virtual ~CreateTransactionHandler();

    virtual void Prepare();

    virtual void Commit();

    virtual void Rollback();

    virtual void Finish();

};


#endif