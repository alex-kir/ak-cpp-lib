#pragma once

#include <ak/enumeration.h>

namespace ak
{
    namespace net
    {
        class socket_protocol : public ak::enumeration
        {
        private:
            socket_protocol(const int val) : ak::enumeration(val) { };
        public:
            const static socket_protocol ipproto_tcp;
            const static socket_protocol ipproto_udp;
        };
    }
}