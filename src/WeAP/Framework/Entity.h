#ifndef __WeAP_Entity_H__
#define __WeAP_Entity_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class Entity : public AppObject
{
public:
    Entity();
    virtual ~Entity();

    virtual void Dump();


private:
    Entity(const Entity& other);
    Entity& operator=(const Entity& other);

    void Init(const Entity& other);

protected:
    virtual void Clear();

protected:

};

}}


#endif //__WeAP_Entity_H__

