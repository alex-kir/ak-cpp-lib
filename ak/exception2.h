#pragma once

#include <sstream>
#include <exception>

namespace ak
{
    class exception : public std::exception
    {
        std::ostringstream * _ss;
        std::string _s;
        exception & operator =(const exception & ex);
    public:
        exception() : _ss(new std::ostringstream())
        { }
        explicit exception(const exception & ex) : _ss(new std::ostringstream())
        {
            (*_ss) << ex._ss->str();
        }
        ~exception()
        {
            delete _ss, _ss = 0;
        }
        virtual const char * what() const
        {
            const_cast<exception*>(this)->_s = _ss->str();
            return _s.c_str();
        }
        template<class T>
        exception & operator << (const T & value)
        {
            (*_ss) << value;
            return *this;
        }
    };
}



