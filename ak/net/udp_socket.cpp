#include <ak/net/udp_socket.h>
#include <ak/net/get_last_error.h>

namespace ak
{
    namespace net
    {
        udp_socket::udp_socket()
            : basic_socket(address_family::inet, socket_type::dgram, socket_protocol::ipproto_udp)
        { }

        udp_socket::udp_socket(int port)
            : basic_socket(address_family::inet, socket_type::dgram, socket_protocol::ipproto_udp)
        {
            socket_address sa(port);
            int r = ::bind(_socket, (SOCKADDR*)sa.ptr(), sa.size());
            if (r == SOCKET_ERROR)
                throw ak::exception() << "::bind() return SOCKET_ERROR : " << get_last_error();
        }

        udp_socket::udp_socket(const std::string & host, int port)
            : basic_socket(address_family::inet, socket_type::dgram, socket_protocol::ipproto_udp)
        {
            socket_address sa(host, port);
            if (::bind(_socket, (SOCKADDR*)sa.ptr(), sa.size()) == SOCKET_ERROR)
                throw ak::exception() << "::bind() return SOCKET_ERROR : " << get_last_error();
        }

        int udp_socket::write(const void * data, int len, const socket_address & sa)
        {
            int n = ::sendto(_socket, (const char*)data, len, MSG_DONTROUTE, (SOCKADDR*)sa.ptr(), sa.size());
            if (n == SOCKET_ERROR)
                throw ak::exception() << "::sendto() return SOCKET_ERROR : " << get_last_error();
            return n;
        }

        int udp_socket::read(void * data, int len, socket_address & sa)
        {
            sockaddr_in sender;
            int sendersize = sizeof(sender);
            int n = ::recvfrom(_socket, (char *)data, len, 0, (SOCKADDR *)&sender, &sendersize);
            if (n == SOCKET_ERROR)
                throw ak::exception() << "::recvfrom() return SOCKET_ERROR : " << get_last_error();
            sa.reset(&sender, sendersize);
            return n;
        }
    }
}
