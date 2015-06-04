#pragma once
#include <ak/cast.h>
namespace ak
{
    class sysobj
    {
    private:
        typedef void * _Type;
        _Type _obj;
    public:
        sysobj()
        {
            _obj = 0;
        }
        template<typename T>
        sysobj(const T t)
        {
            object<T>(t);
        }
    public:
        _Type object() const
        {
            return _obj;
        }

        void object(_Type t)
        {
            _obj = t;
        }

        bool empty() const
        {
            return _obj == 0 || _obj == (_Type)(-1);
        }
    public:
        template<typename T>
        operator T () const
        {
            return object<T>();
        }

        template<typename T>
        T object() const
        {
            return ak::cast_ri<T>(_obj);
        }

        template<typename T>
        void object(T t)
        {
            _obj = ak::cast_ri<_Type>(t);
        }

        template<typename T>
        T handle() const
        {
            return object<T>();
        }

        template<typename T>
        void handle(T t)
        {
            object<_Type>(t);
        }
    };
}