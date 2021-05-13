#pragma once
#include <ak/strings/string_operations.h>
#include <ak/cast.h>
#include <string>
#include <vector>

namespace ak
{
    namespace string
    {
        class format
        {
            std::vector<std::string> _f1, _f2;

        public:
            format(std::string f)
            {
                ak::string::split(f, "%%", _f1, true);
            };
            operator std::string ()
            {
                std::string retval = _f1.size() > 0 ? _f1[0] : ""; 
                for (size_t i = 1; i < _f1.size(); i++)
                {
                    if (_f2.size() >= i)
                        retval += _f2[i - 1];
                    retval += _f1[i];
                }
                return retval;
            }
            template<typename T>
            format & operator % (const T & t)
            {
                _f2.push_back(ak::cast<std::string>(t));
                return *this;
            }
            format & operator % (const std::string & t)
            {
                _f2.push_back(t);
                return *this;
            }
        };

    }
}