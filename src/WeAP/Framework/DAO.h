#ifndef __WeAP_DAO_H__
#define __WeAP_DAO_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class DAO : public AppObject
{
public:
    DAO();
    virtual ~DAO();

    virtual void Dump();


private:
    DAO(const DAO& other);
    DAO& operator=(const DAO& other);

    void Init(const DAO& other);

protected:
    virtual void Clear();

protected:

};

}}


#endif //__WeAP_DAO_H__

