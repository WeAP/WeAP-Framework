#include "Handler.h"


class DTHandler : public Handler
{
public:
    DTHandler();
    virtual ~DTHandler();

    virtual void Prepare(){};

    virtual void Commit(){};

    virtual void Rollback(){};

};