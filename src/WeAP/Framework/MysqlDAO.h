#ifndef __WeAP_MysqlDAO_H__
#define __WeAP_MysqlDAO_H__

#include "AppObject.h"
#include "ObjectList.h"

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

    void Query(const string& sql, KVMap& record);
    void Query(const string& sql, ObjectList<KVMap>& recordList);
    //void Insert(const string& sql,)
    //void Update(const string& sql);
    

private:
    MysqlDAO(const MysqlDAO& other);
    MysqlDAO& operator=(const MysqlDAO& other);

protected:

};

}}


#endif //__WeAP_MysqlDAO_H__

