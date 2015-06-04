#pragma once
#include <ak/exception.h>
namespace ak
{
    template<class T>
    T cast(const T & t)
    {
        return t;
    }

    template<class T>
    T cast(T & t)
    {
        return t;
    }

    template<class TResult, class T>
    TResult cast(const T & t)
    {
        std::stringstream ss;
        ss << t;
        TResult tresult;
        ss >> tresult;
        return tresult;
    }

    template<class T1, class T2>
    T1 cast_ri(const T2 t2)
    {
        int detect_size_errors[sizeof(T1) == sizeof(T2) ? 1 : -1] = {};
#pragma warning (push)
#pragma warning (disable:4311)
#pragma warning (disable:4312)
        return reinterpret_cast<T1>(t2);
#pragma warning (pop)
    }
}
