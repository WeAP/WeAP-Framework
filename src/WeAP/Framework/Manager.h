#ifndef __WeAP_Manager_H__
#define __WeAP_Manager_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class Manager : public AppObject
{
public:
    Manager();
    virtual ~Manager();

private:
    Manager(const Manager& other);
    Manager& operator=(const Manager& other);

protected:

};

}}


#endif //__WeAP_Manager_H__

