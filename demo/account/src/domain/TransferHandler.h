#ifndef __WeAP_TransferHandler_H__
#define __WeAP_TransferHandler_H__

#include "DTHandler.h"

using namespace WeAP::Framework;

class TransferHandler : public DTHandler
{
public:
    TransferHandler();
    virtual ~TransferHandler();

    virtual void Prepare();

    virtual void Commit();

    virtual void Rollback();

    virtual void Finish();

};


#endif