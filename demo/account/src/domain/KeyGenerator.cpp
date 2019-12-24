#include "KeyGenerator.h"

using namespace WeAP::System;

KeyGenerator::KeyGenerator()
{
}

KeyGenerator::~KeyGenerator()
{
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
