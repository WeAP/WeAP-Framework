#include "KeyGenerator.h"
#include "Convert.h"



using namespace WeAP::System;


KeyGenerator::KeyGenerator()
{
}

KeyGenerator::~KeyGenerator()
{
}


string KeyGenerator::GenTXNNo()
{
    //todo Redis 
    static unsigned int seq = 0;

    return Convert::ToString(time(NULL) * 100 + seq++);
}


uint64_t KeyGenerator::NewAccountId()
{
    static unsigned int seq = 0;

    return time(NULL) * 100 + seq++;
}


uint64_t KeyGenerator::NewAccountTransactionId()
{
    static unsigned int seq = 0;

    return time(NULL) * 1000 + seq++;
}
