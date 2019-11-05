#ifndef __WeAP_Singleton_H__
#define __WeAP_Singleton_H__

#include <cstddef>  // for NULL
#include "stdio.h"

/**
 * 
 *
 * usage 1:class CMemProxy : public Singleton<CMemProxy>
 * usage 2: typedef Singleton<CMemProxy> CMemSingleton;
 *
 * @author xzwang
 * @date 2012-10
 */
template<typename T>
class Singleton
{
public:
    virtual ~Singleton() { }
    static T *GetInstance()
    {
        if (NULL == instance)
        {
            NewInstance();
        }

        return instance;
    }


    static T *NewInstance()
    {
        if(NULL != instance)
        {
            delete instance;
            instance = NULL;
        }

        instance = new T();
        return instance;
    }


    static void DeleteInstance()
    {
        if(NULL != instance)
        {
            delete instance;
            instance = NULL;
       }
   }

protected:
    Singleton() { };

    static T *instance;


private:
    Singleton(const Singleton &other);
    Singleton &operator=(const Singleton &other);
};

template<class T> T *Singleton<T>::instance = NULL;



#endif //__WeAP_Singleton_H__
