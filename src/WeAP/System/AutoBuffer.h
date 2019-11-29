#ifndef __WeAP_AutoBuffer_H__
#define __WeAP_AutoBuffer_H__

#include "Object.h"

using namespace std;

namespace WeAP { namespace System {

/**
 * 
 * 
 * @author xzwang
 */
class AutoBuffer: public Object
{
public:
    AutoBuffer(size_t size);
    virtual ~AutoBuffer();

    char **operator &() { return &this->buffer; }

    char* Get();
    size_t GetSize() const;
    string ToString() const;

protected:
    char* buffer;
    size_t size;

};


}}

#endif //__WeAP_AutoBuffer_H__
