#ifndef __WeAP_KeyGenerator_H__
#define __WeAP_KeyGenerator_H__

#include "AppObject.h"



using namespace WeAP::Framework;


class KeyGenerator : public AppObject
{
public:
    KeyGenerator();
    virtual ~KeyGenerator();

    string GenTXNNo();

    uint64_t NewAccountId();

    uint64_t NewAccountTransactionId();

public:


};


#endif 
