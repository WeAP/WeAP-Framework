#ifndef __WeAP_AccountTransferHandler_H__
#define __WeAP_AccountTransferHandler_H__

#include "DTHandler.h"

using namespace WeAP::Framework;

class AccountTransferHandler : public DTHandler
{
public:
    AccountTransferHandler();
    virtual ~AccountTransferHandler();

    virtual void Prepare();

    virtual void Commit();

    virtual void Rollback();

    virtual void Finish();

};


#endif