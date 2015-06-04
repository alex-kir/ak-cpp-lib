#pragma once

namespace ak
{
    template<typename T, typename M>
    class _predicate_bynary
    {
        M m;
    public:
        _predicate_bynary(M method)
        {
            m = method;
        }
        bool operator () (const T & l, const T & r)
        {
            return (l.*m)() < (r.*m)();
        }
    };

    template<typename T, typename M, typename V, typename F>
    class _predicate_unary
    {
        M m;
        const V & v;
        F & f;
    public:
        _predicate_unary(M method, const V & value, F & func)
            : m(method)
            , v(value)
            , f(func)
        { }

        bool operator () (const T & l)
        {
            return f(((l.*m)()), v);
        }
    };

    template<typename T, typename M>
    _predicate_bynary<T, M> predicate_for_getter(M method)
    {
        return _predicate_bynary<T, M>(method);
    }

    template<typename T, typename M>
    _predicate_bynary<T, M> predicate_for_getter(const std::vector<T> & v, M method)
    {
        return _predicate_bynary<T, M>(method);
    }

    template<typename T, typename M, typename V, typename F>
    _predicate_unary<T, M, V, F> predicate_unary(M method, V value, F func)
    {
        return _predicate_unary<T, M, V, F>(method, value, func);
    }
}