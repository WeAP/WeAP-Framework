#ifndef __WeAP_UrlPackage_H__
#define __WeAP_UrlPackage_H__

#include "Package.h"
#include "KVMap.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class UrlPackage : public Package
{
public:
    UrlPackage();
    virtual ~UrlPackage();

    void Parse(const string& str, char sep1 = '&', char sep2 = '=');
    void ToString();

private:
    UrlPackage(const UrlPackage& other);
    UrlPackage& operator=(const UrlPackage& other);

protected:
    KVMap params;
    ObjectMap<KVMap> subParams;

};

}}


#endif //__WeAP_UrlPackage_H__

