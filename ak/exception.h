#pragma once

#include <sstream>
#include <exception>

namespace ak
{
    class exception : public std::exception
    {
        std::ostringstream * _ss;
        std::string _s;
		exception & operator =(const exception & other);
		exception & operator =(exception && other);
		exception(exception && other);
    public:
        exception() : _ss(new std::ostringstream())
        { }
        exception(const exception & other) : _ss(new std::ostringstream())
        {
			(*_ss) << other._ss->str();
        }
		//exception & operator =(const exception & other){ return *this; } // tmp
		//exception & operator =(exception && other){ return *this; } // tmp
		//exception(exception && other){} // tmp

        ~exception()
        {
            delete _ss, _ss = 0;
        }
        virtual const char * what() const throw()
        {
            const_cast<exception*>(this)->_s = _ss->str();
            return _s.c_str();
        }
        template<class T>
        const exception & operator << (const T & value) const
        {
            (*_ss) << value;
            return *this;
        }
    };
}



