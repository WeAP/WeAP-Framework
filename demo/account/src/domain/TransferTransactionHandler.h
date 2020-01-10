#ifndef __WeAP_TransferTransactionHandler_H__
#define __WeAP_TransferTransactionHandler_H__

#include "STHandler.h"

using namespace WeAP::Framework;

class TransferTransactionHandler : public STHandler
{
public:
    TransferTransactionHandler();
    virtual ~TransferTransactionHandler();

    virtual void Prepare();

    virtual void Commit();

    virtual void Rollback();

    virtual void Finish();

};


#endif