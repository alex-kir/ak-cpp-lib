#pragma once

namespace ak
{
    template<typename T2>
    struct size;

    template<typename T1>
    struct point
    {
        T1 x, y;

        point() : x(0), y(0)
        { }

        point(T1 x1, T1 y1) : x(x1), y(y1)
        { }

        template<typename T2>
        point(const point<T2> & pt) : x(pt.x), y(pt.y)
        { }

        template<typename T2>
        const point<T1> operator + (const point<T2> & pt)
        {
            return point<T1>(x + pt.x, y + pt.y);
        }

        template<typename T2>
        const point<T1> operator - (const point<T2> & pt)
        {
            return point<T1>(x - pt.x, y - pt.y);
        }
        
        template<typename T2>
        const point<T1> operator + (const size<T2> & sz) const
        {
            return point<T1>(x + sz.width, y + sz.height);
        }
        
        template<typename T2>
        const point<T1> operator - (const size<T2> & sz) const
        {
            return point<T1>(x - sz.width, y - sz.height);
        }

        template<typename T2>
        bool operator == (const point<T2> & that) const
        {
            return x == that.x && y == that.y;
        }

        template<typename T2>
        bool operator != (const point<T2> & that) const
        {
            return x != that.x || y != that.y;
        }
    };

    typedef point<int> pointi;
    typedef point<double> pointd;
}