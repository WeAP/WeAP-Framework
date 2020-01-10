#ifndef __WeAP_TransferOutHandler_H__
#define __WeAP_TransferOutHandler_H__

#include "STHandler.h"

using namespace WeAP::Framework;

class TransferOutHandler : public STHandler
{
public:
    TransferOutHandler();
    virtual ~TransferOutHandler();

    virtual void Prepare();

    virtual void Commit();

    virtual void Rollback();

    virtual void Finish();

};


#endif