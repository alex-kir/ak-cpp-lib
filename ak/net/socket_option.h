#pragma once

#include <ak/enumeration.h>

namespace ak
{
    namespace net
    {
        class socket_option : public ak::enumeration
        {
        private:
            socket_option(const int val) : ak::enumeration(val) { };
        public:
            const static socket_option broadcast;
        };
    }
}