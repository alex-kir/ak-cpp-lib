#pragma once
#include <ak/exception.h>
#include <ak/text/text.h>
namespace ak
{
    namespace reflection
    {
        template<typename T>
        std::string _typename_of_impl(const T &)
        {
            return ak::string::between(__FUNCSIG__, "ak::reflection::_typename_of_impl<", ">(");
        }

        template<typename T>
        std::string typename_of(const T & t)
        {
            return _typename_of_impl(t);
            ////char c[-1];
            //throw ak::exception() << "undefined type";
        }


    }
}
