#ifndef __WeAP_Manager_H__
#define __WeAP_Manager_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class Manager : public AppObject
{
public:
    Manager();
    virtual ~Manager();

    virtual void Dump();


private:
    Manager(const Manager& other);
    Manager& operator=(const Manager& other);

    void Init(const Manager& other);

protected:
    virtual void Clear();

protected:

};

}}


#endif //__WeAP_Manager_H__

