#ifndef __WeAP_DAO_H__
#define __WeAP_DAO_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class DAO : public AppObject
{
public:
    DAO();
    virtual ~DAO();

private:
    DAO(const DAO& other);
    DAO& operator=(const DAO& other);

protected:

};

}}


#endif //__WeAP_DAO_H__

