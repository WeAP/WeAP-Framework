#ifndef __WeAP_Entity_H__
#define __WeAP_Entity_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {


#define COPY_FIELD(fieldName, dataType )  \
    if (record.Exist(#fieldName))  \
    {\
        this->fieldName = record.Get##dataType(#fieldName);\
    }

#define EQUAL_FIELD(fieldName)            \
    if (this->fieldName != other.fieldName) \
    {                                     \
        return false;                     \
    }



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

    virtual string GenDataSign() const { return "";};

};

}}


#endif //__WeAP_Entity_H__

