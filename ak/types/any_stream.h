#pragma once
#include <ak/types/any.h>
#include <queue>
namespace ak
{
    namespace types
    {
        class any_stream
        {
            std::queue<any> data;
        public:
            template<typename T>
            any_stream & operator << (const T & t)
            {
                any a;
                a = t;
                data.push(a);
                return *this;
            }

            any_stream & operator << (const char * t)
            {
                *this << std::string(t);
                return *this;
            }

            template<typename T>
            any_stream & operator >> (T & t)
            {
                auto a = data.front();
                data.pop();
                t = (T)a;
                return *this;
            }
        };
    }
}
