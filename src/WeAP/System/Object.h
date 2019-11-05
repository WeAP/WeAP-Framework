#ifndef __WeAP_Object_H__
#define __WeAP_Object_H__

#include "stdinc.h"
#include "Logger.h"
#include "Defines.h"

using namespace std;

namespace WeAP { namespace System {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-09
 */
class Object
{
public:
    Object();
    Object(const Object& other);
    virtual ~Object();
    
    Object& operator=(const Object& other);

    virtual void Dump();

protected:
    void Init(const Object& other);


};


}}

#endif //__WeAP_Object_H__
