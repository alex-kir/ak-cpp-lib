#include <ak/net/socket_protocol.h>

namespace ak
{
    namespace net
    {
        const socket_protocol socket_protocol::ipproto_tcp(IPPROTO_TCP);
        const socket_protocol socket_protocol::ipproto_udp(IPPROTO_UDP);
    }
}
