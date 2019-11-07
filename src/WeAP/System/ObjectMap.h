#ifndef __WeAP_ObjectMap_H__
#define __WeAP_ObjectMap_H__

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
class ObjectMap : public Object
{
public:
    ObjectMap(){};
    virtual ~ObjectMap()
    {
        for (map<string, T*>::const_iterator it = this->innerMap.begin(); it != this->innerMap.end(); ++it)
        {
            delete it->second;
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
        return this->Get(const string& key);
    };

    T* Get(const string& key)
    {
        if (!this->Exist(key))
        {
            ERROR("ObjectMap Get out of range, index=%d", index);
            throw CException(Error::ERR_OBJECT_LIST_GET_OUT_OF_RANGE, "ObjectList Get out of range");
        }

        return this->innerMap[key];
    };


    const T* Get(const string& key) const
    {
        if (!this->Exist(key))
        {
            ERROR("ObjectMap Get out of range, index=%d", index);
            throw CException(Error::ERR_OBJECT_LIST_GET_OUT_OF_RANGE, "ObjectList Get out of range");
        }

        return this->innerMap.at(index);
    };


    bool Exist(const string& key) const
    {
        map<string, T*>::const_iterator iter = this->innerMap.find(key);
        if (iter != this->innerMap.end())
        {
            return true;
        }

        return false;
    };


    //void Delete()


    size_t GetCount()  const
    { 
        return this->innerMap.size();
    };

    string ToString(char sep) const
    {
        string str;

        int i = 0;
        for (map<string, T*>::const_iterator it = this->innerMap.begin(); it != this->innerMap.end(); ++it)
        {
            if (i != 0)
            {
                str += sep;
            }
            str += it.frist;
            str += ":";
            str += it.second->ToString();
            i++;
        }

        return str;
    }

private:
    ObjectMap(const ObjectMap& other);
    ObjectMap& operator=(const ObjectMap& other);

protected:
    map<string, T*> innerMap;

};

}}


#endif //__WeAP_ObjectMap_H__

