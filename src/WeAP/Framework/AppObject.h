#ifndef __WeAP_AppObject_H__
#define __WeAP_AppObject_H__

#include "Object.h"
#include "Error.h"
#include "Exception.h"

using namespace WeAP::System;

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class AppObject : public WeAP::System::Object
{
public:
    AppObject();
    virtual ~AppObject();

private:
    AppObject(const AppObject& other);
    AppObject& operator=(const AppObject& other);

};

}}


#endif //__WeAP_AppObject_H__

