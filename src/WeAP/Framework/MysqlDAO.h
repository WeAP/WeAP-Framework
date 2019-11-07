#ifndef __WeAP_MysqlDAO_H__
#define __WeAP_MysqlDAO_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class MysqlDAO : public AppObject
{
public:
    MysqlDAO();
    virtual ~MysqlDAO();

    void Init(const INIConfig& config, const string& section);
    

private:
    MysqlDAO(const MysqlDAO& other);
    MysqlDAO& operator=(const MysqlDAO& other);

protected:

};

}}


#endif //__WeAP_MysqlDAO_H__

