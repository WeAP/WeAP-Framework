#ifndef __WeAP_Routine_H__
#define __WeAP_Routine_H__

#include "AppObject.h"

namespace WeAP { namespace Framework {

/**
 * a list of instructions that enable a computer to perform a particular task,
 * include cgi, rpc, daemon, crontab task
 * 
 * @author xzwang
 */
class Routine : public AppObject
{
public:
    Routine();
    virtual ~Routine();

    //void Execute() = 0;

private:
    Routine(const Routine& other);
    Routine& operator=(const Routine& other);

};

}}


#endif //__WeAP_Routine_H__

