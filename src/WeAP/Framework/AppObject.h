#ifndef __WeAP_AppObject_H__
#define __WeAP_AppObject_H__

#include "Object.h"

using namespace WeAP::System;

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
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

