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

    virtual void Dump();


private:
    Package(const Package& other);
    Package& operator=(const Package& other);

    void Init(const Package& other);

protected:
    virtual void Clear();

protected:

};

}}


#endif //__WeAP_Package_H__

