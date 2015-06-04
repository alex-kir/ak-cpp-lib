#pragma once

#include <ak/exception.h>

namespace ak
{
    template<class T>
    class ref
    {
        T * _t;
    public:
        explicit ref(T * t)
        {
            _t = t;
        }
        explicit ref(T & t)
        {
            _t = &t;
        }
        explicit ref(ref<T> & r)
        {
            _t = r._t;
        }
        T * operator ->()
        {
            if (_t == 0)
            {
                throw exception() << "ref is null";
            }
            return _t;
        }
    };
}