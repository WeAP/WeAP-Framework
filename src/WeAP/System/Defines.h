
#ifndef __WEAP_DEFINES_H__
#define __WEAP_DEFINES_H__

#include <limits>
#include <stdint.h>

#include <string>


//#define NAMESPACE_BEGIN namespace WeAP { namespace System {
//#define NAMESPACE_END }}


using std::string;
namespace WeAP { namespace System {


typedef short int int16;
typedef unsigned short int uint16;

typedef long int int32;
typedef unsigned int uint32;

typedef long long int int64;
typedef unsigned long long int uint64;

const unsigned int SIZE_1K = 1024;
const unsigned int SIZE_2K = SIZE_1K * 2;
const unsigned int SIZE_4K = SIZE_1K * 4;
const unsigned int SIZE_8K = SIZE_1K * 8;
const unsigned int SIZE_16K = SIZE_1K * 16;
const unsigned int SIZE_32K = SIZE_1K * 32;
const unsigned int SIZE_64K = SIZE_1K * 64;
const unsigned int SIZE_128K = SIZE_1K * 128;
const unsigned int SIZE_256K = SIZE_1K * 256;
const unsigned int SIZE_512K = SIZE_1K * 512;

const unsigned int SIZE_1M = SIZE_1K * SIZE_1K;
const unsigned int SIZE_2M = SIZE_1M * 2;
const unsigned int SIZE_4M = SIZE_1M * 4;
const unsigned int SIZE_8M = SIZE_1M * 8;
const unsigned int SIZE_16M = SIZE_1M * 16;
const unsigned int SIZE_32M = SIZE_1M * 32;
const unsigned int SIZE_64M = SIZE_1M * 64;
const unsigned int SIZE_128M = SIZE_1M * 128;
const unsigned int SIZE_256M = SIZE_1M * 256;
const unsigned int SIZE_512M = SIZE_1M * 512;


const int MinInt = std::numeric_limits<int>::min();
const int MaxInt = std::numeric_limits<int>::max();

const int64 MinInt64 = std::numeric_limits<int64>::min();
const int64 MaxInt64 = std::numeric_limits<int64>::max();


}}

#endif //__WEAP_DEFINES_H__




