#ifndef __WeAP_INIConfig_H__
#define __WeAP_INIConfig_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 */
class INIConfig : public AppObject
{

public:
    INIConfig();
    virtual ~INIConfig();

    void Init(const string& confFile);


private:
    INIConfig(const INIConfig& other);
    INIConfig& operator=(const INIConfig& other);

protected:
    string confFile;

};

}}


#endif //__WeAP_INIConfig_H__

