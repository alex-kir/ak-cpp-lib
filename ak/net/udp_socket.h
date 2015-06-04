#pragma once
#include <ak/net/basic_socket.h>
#include <ak/net/socket_address.h>

namespace ak
{
    namespace net
    {
        class udp_socket : public basic_socket
        {
        public:
            udp_socket();
            udp_socket(int port);
            udp_socket(const std::string & host, int port);

            int write(const void * data, int len, const socket_address & sa);
            int read(void * data, int len, socket_address & sa);
        };
    }
}