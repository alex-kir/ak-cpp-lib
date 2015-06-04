#include <ak/net/socket_type.h>

namespace ak
{
    namespace net
    {
        const socket_type socket_type::stream(SOCK_STREAM);
        const socket_type socket_type::dgram(SOCK_DGRAM);
    }
}
