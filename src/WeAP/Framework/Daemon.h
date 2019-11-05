#ifndef __WeAP_Daemon_H__
#define __WeAP_Daemon_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * 
 * 
 * @author xzwang
 * @date 2018-05-11
 */
class Daemon : public AppObject
{
public:
    Daemon();
    virtual ~Daemon();

    virtual void Dump();


private:
    Daemon(const Daemon& other);
    Daemon& operator=(const Daemon& other);

    void Init(const Daemon& other);

protected:
    virtual void Clear();

protected:

};

}}


#endif //__WeAP_Daemon_H__

