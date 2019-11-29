#include "AutoBuffer.h"



namespace WeAP{ namespace System {



AutoBuffer::AutoBuffer(size_t size)
{
    this->buffer = (char*)malloc(size + 1); 
    this->size = size;

}


AutoBuffer::~AutoBuffer()
{
    if (this->buffer != NULL)
    {
        free(this->buffer); 
        this->buffer = NULL; 
    }
}

char* AutoBuffer::Get()
{
    return this->buffer;
}


size_t AutoBuffer::GetSize() const
{
    return this->size;
}

string AutoBuffer::ToString() const
{
    return string(this->buffer, this->size + 1);
}


}}
