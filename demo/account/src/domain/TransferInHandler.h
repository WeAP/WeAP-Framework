#ifndef __WeAP_TransferInHandler_H__
#define __WeAP_TransferInHandler_H__

#include "STHandler.h"

using namespace WeAP::Framework;

class TransferInHandler : public STHandler
{
public:
    TransferInHandler();
    virtual ~TransferInHandler();

    virtual void Prepare();

    virtual void Commit();

    virtual void Rollback();

    virtual void Finish();

};


#endif