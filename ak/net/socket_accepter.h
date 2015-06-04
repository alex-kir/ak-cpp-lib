#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <ak/misc/nocopy.h>

namespace ak
{
    namespace net
    {
        class socket_accepter : public basic_socket
        {
        public:
            void bind(const std::string & host, int port);
            void accept(socket & sock);
        };
    }
}
