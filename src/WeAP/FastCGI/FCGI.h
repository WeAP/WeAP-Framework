#ifndef __WeAP_FCGI_H__
#define __WeAP_FCGI_H__

#include <fcgi_stdio.h>
#include "Routine.h"

using namespace WeAP::System;

namespace WeAP { namespace FastCGI {

class FCGI: public Routine
{
public:
    FCGI();
    virtual ~FCGI();


protected:


};

}}

#endif

