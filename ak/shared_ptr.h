#pragma once
#include <boost/shared_ptr.hpp>

namespace ak
{

    //template<class T>
    //typedef boost::shared_ptr<int> shared_ptr<int>;

    //template<class _T1>
    //class shared_ptr 
    //{
    //    friend class shared_ptr;
    //private:
    //    _T1 * _t;
    //    int * _c;
    //public:
    //    shared_ptr()
    //    { }

    //    explicit shared_ptr(const _T1 * t)
    //    {
    //        _t = const_cast<_T1*>(t);
    //        _c = new int(0);
    //        _addref();
    //    }

    //    ~shared_ptr()
    //    {
    //        _release();
    //    }

    //    template<typename _T2>
    //    shared_ptr<_T1>(const shared_ptr<_T2> & _T2)
    //    {
    //        _t = static_cast<_T1*>(_T2._t);
    //        _c = _T2._c;
    //        _addref();
    //    }

    //    template<typename _T2>
    //    void operator = (const shared_ptr<_T2> & _T2)
    //    {
    //        _release();
    //        _t = static_cast<_T1>(_T2._t);
    //        _c = _T2._c;
    //        _addref();
    //    }

    //    _T1 * operator ->()
    //    {
    //        return (_T1 *)_t;
    //    }

    //    _T1 & operator *()
    //    {
    //        return *_t;
    //    }

    //    bool operator !()
    //    {
    //        return !(_t);
    //    }

    //    //operator _T1 * ()
    //    //{
    //    //    return _t;
    //    //}

    //    _T1 * get()
    //    {
    //        return _t;
    //    }
    //private:
    //    void _addref()
    //    {
    //        if (_c != 0)
    //        {
    //            (*_c)++;
    //        }
    //    }

    //    void _release()
    //    {
    //        if (_c != 0)
    //        {
    //            (*_c)--;
    //            if ((*_c) == 0)
    //            {
    //                delete _c, _c = 0;
    //                delete _t, _t = 0;
    //            }
    //        }
    //    }
    //};

    //template<class T>
    //shared_ptr<T> create_shared_ptr(T * ptr)
    //{
    //    return shared_ptr<T>(ptr);
    //}

}



