#ifndef __WeAP_Package_H__
#define __WeAP_Package_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class Package : public AppObject
{
public:
    Package();
    virtual ~Package();


private:
    Package(const Package& other);
    Package& operator=(const Package& other);

};

}}


#endif //__WeAP_Package_H__

