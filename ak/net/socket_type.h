#pragma once

#include <ak/enumeration.h>

namespace ak
{
    namespace net
    {
        class socket_type : public ak::enumeration
        {
        private:
            socket_type(const int val) : ak::enumeration(val) { };
        public:
            const static socket_type stream;
            const static socket_type dgram;
        };
    }
}