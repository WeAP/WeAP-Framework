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
    return time(NULL);
}


