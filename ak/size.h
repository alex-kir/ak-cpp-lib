#pragma once

namespace ak
{
    namespace types
    {
        template<typename T1>
        struct point;
    }

    using ak::types::point;

    template<typename T1>
    struct size
    {
        T1 width, height;

        size() : width(0), height(0)
        { }

        size(T1 w, T1 h) : width(w), height(h)
        { }

        template<typename T2>
        size(const size<T2> & sz) : width(sz.width), height(sz.height)
        { }

        template<typename T2>
        size(const point<T2> & pt) : width(pt.x), height(pt.y)
        { }

        template<typename T2>
        const size<T1> operator + (const point<T2> & pt)
        {
            return size<T1>(width + pt.x, height + pt.y);
        }

        template<typename T2>
        const size<T1> operator - (const point<T2> & pt)
        {
            return size<T1>(width - pt.x, height - pt.y);
        }
        
        template<typename T2>
        const size<T1> operator + (const size<T2> & sz)
        {
            return size<T1>(width + sz.width, height + sz.height);
        }
        
        template<typename T2>
        const size<T1> operator - (const size<T2> & sz)
        {
            return size<T1>(width - sz.width, height - sz.height);
        }

        const size<T1> operator / (T1 val)
        {
            return size<T1>(width / val, height / val);
        }
    };

    typedef size<int> sizei;
    typedef size<double> sized;
}