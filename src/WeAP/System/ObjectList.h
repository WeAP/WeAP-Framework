#ifndef __WeAP_ObjectList_H__
#define __WeAP_ObjectList_H__

#include "Object.h"
#include "Error.h"
#include "Exception.h"

namespace WeAP { namespace System {

/**
 * 
 * 
 * @author xzwang
 */
template<typename T>
class ObjectList : public Object
{
public:
    ObjectList(){};
    virtual ~ObjectList()
    {
        const size_t size = this->innerList.size();
        for(size_t i = 0; i < size; i++)
        {
            delete this->innerList[i];
            this->innerList[i] = NULL;
        }    
    };

    T* Add()
    {    
        T* obj = new T();
        this->innerList.push_back(obj);
        return obj;
    };


    bool operator==(const ObjectList<T>& other) const
    {
        if(this == &other)
        {
            return true;
        }

        if (this->innerList.size() != other.innerList.size())
        {
            return false;
        }
 
        const size_t size = this->innerList.size();
        for(size_t i = 0; i < size; i++)
        {
            if (!(*(this->innerList.at(i)) == *(other.innerList.at(i))))
            {
                DEBUG("ObjectList not equal,i=%d", i);
                return false;
            }            
        }

        return true;        
    };

    T* operator[](size_t index)
    {
        return this->Get(index);
    };

    T* Get(size_t index)
    {
        if (index > this->innerList.size() -1)
        {
            ERROR("ObjectList Get out of range, index=%d", index);
            throw Exception(Error::ObjectList_Get_Out_Of_Range, "ObjectList Get out of range");
        }

        return this->innerList[index];
    };


    const T* Get(size_t index) const
    {
        if (index > this->innerList.size() -1)
        {
            ERROR("ObjectList Get out of range, index=%d", index);
            throw Exception(Error::ObjectList_Get_Out_Of_Range, "ObjectList Get out of range");
        }

        return this->innerList.at(index);
    };


    bool Exist(size_t index)
    {
        if (index < this->innerList.size())
        {
            return true;
        }

        return false;
    };

    T* Find(size_t index)
    {
        if (index < this->innerList.size())
        {
            return this->innerList[index];
        }

        return NULL;
    };

    //void Delete()


    size_t GetCount()  const
    { 
        return this->innerList.size();
    };

    string ToString(char sep)
    {
        string str;
        const size_t size = this->innerList.size();
        for(size_t i = 0; i < size; i++)
        {
            if (i != 0)
            {
                str += sep;
            }
            str += this->innerList[i]->ToString();
            
        }
        return str;
    }

private:
    ObjectList(const ObjectList& other);
    ObjectList& operator=(const ObjectList& other);

protected:
    vector<T*> innerList;

};

}}


#endif //__WeAP_ObjectList_H__

