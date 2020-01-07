#ifndef __WeAP_ObjectMap_H__
#define __WeAP_ObjectMap_H__

#include "Object.h"
#include "Error.h"
#include "Exception.h"
#include "Logger.h"

namespace WeAP { namespace System {

/**
 * 
 * 
 * @author xzwang
 */
template<typename T>
class ObjectMap : public Object
{
protected:
    typedef map<string, void*>::iterator Iterator;
    typedef map<string, void*>::iterator ConstIterator;
public:
    ObjectMap(){};
    virtual ~ObjectMap()
    {
        for (ConstIterator it = this->innerMap.begin(); it != this->innerMap.end(); ++it)
        {
            delete (T*)it->second;
            it->second = NULL;
        }
    
        this->innerMap.clear();
  
    };

    T* Add(const string& key)
    {    
        T* obj = new T();
        this->innerMap[key] = obj;
        return obj;
    };


    T* operator[](const string& key)
    {
        return this->Get(key);
    };

    T* Get(const string& key)
    {
        if (!this->Exist(key))
        {
            ERROR("ObjectMap Get out of range, index=%d", index);
            throw Exception(Error::ObjectList_Get_Out_Of_Range, "ObjectList Get out of range");
        }

        return (T*)this->innerMap[key];
    };


    const T* Get(const string& key) const
    {
        if (!this->Exist(key))
        {
            ERROR("ObjectMap Get out of range, index=%s", key.c_str());
            throw Exception(Error::ObjectList_Get_Out_Of_Range, "ObjectList Get out of range");
        }

        return (const T*)this->innerMap.at(key);
    };


    bool Exist(const string& key) const
    {
        if (this->innerMap.find(key) != this->innerMap.end())
        {
            return true;
        }

        return false;
    };

    size_t GetCount()  const
    { 
        return this->innerMap.size();
    };

    string ToString(char sep) const
    {
        string str;

        int i = 0;
        
        for (ConstIterator it = this->innerMap.begin(); it != this->innerMap.end(); ++it)
        {
            if (i != 0)
            {
                str += sep;
            }
            str += it->first;
            str += ":";
            str += ((const T*)it->second)->ToString();
            i++;
        }

        return str;
    }

private:
    ObjectMap(const ObjectMap& other);
    ObjectMap& operator=(const ObjectMap& other);

protected:
    map<string, void*> innerMap;

};

}}


#endif //__WeAP_ObjectMap_H__

