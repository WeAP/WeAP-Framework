#ifndef __WeAP_Handler_H__
#define __WeAP_Handler_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class Handler : public AppObject
{
public:
    Handler();
    virtual ~Handler();

private:
    Handler(const Handler& other);
    Handler& operator=(const Handler& other);


protected:

};

}}


#endif //__WeAP_Handler_H__

