#include <ak/net/socket_address.h>
#include <ak/cast.h>
#include <ak/exception.h>
namespace ak
{
    namespace net
    {
        socket_address::socket_address()
        { }

        socket_address::socket_address(const address_family & family, const std::string & host, int port)
        {
            sockaddr_in addr;
            memset(&addr, 0, sizeof(sockaddr_in));
            addr.sin_family = family;
            addr.sin_addr.s_addr = inet_addr(name2ip(host).c_str());
            addr.sin_port = htons(port);
            reset(&addr, sizeof(addr));
        }

        socket_address::socket_address(const std::string & host, int port)
        {
            sockaddr_in addr;
            memset(&addr, 0, sizeof(addr));
            addr.sin_family = address_family::inet;
            addr.sin_addr.s_addr = ::inet_addr(name2ip(host).c_str());
            addr.sin_port = ::htons(port);
            reset(&addr, sizeof(addr));
        }

        socket_address::socket_address(unsigned int host, int port)
        {
            sockaddr_in addr;
            memset(&addr, 0, sizeof(sockaddr_in));
            addr.sin_family = address_family::inet;
            addr.sin_addr.s_addr = htonl(host);
            addr.sin_port = htons(port);
            reset(&addr, sizeof(addr));
        }

        socket_address::socket_address(int port)
        {
            sockaddr_in addr;
            memset(&addr, 0, sizeof(sockaddr_in));
            addr.sin_family = address_family::inet;
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
            addr.sin_port = htons(port);
            reset(&addr, sizeof(addr));
        }

        void socket_address::reset(void * data, int len)
        {
            byte * first = (byte *)data;
            byte * last = first + len;
            _cdata.assign(first, last);
        };

        std::string socket_address::host() const
        {
            if (size() < sizeof(sockaddr_in))
                throw ak::exception() << "not initialized";
            sockaddr_in * p = (sockaddr_in *)ptr();
            std::stringstream ss;
            ss << (int)p->sin_addr.S_un.S_un_b.s_b1 << "."
                << (int)p->sin_addr.S_un.S_un_b.s_b2 << "."
                << (int)p->sin_addr.S_un.S_un_b.s_b3 << "."
                << (int)p->sin_addr.S_un.S_un_b.s_b4;
            return ss.str();
        }

        int socket_address::port() const
        {
            if (size() < sizeof(sockaddr_in))
                throw ak::exception() << "not initialized";
            sockaddr_in * p = (sockaddr_in *)ptr();
            return htons(p->sin_port);
        }

        std::string socket_address::location() const
        {
            return host() + ":" + ak::cast<std::string>(port());
        }

        std::string socket_address::name2ip(const std::string & name)
        {
            win32::wsa::startup();
            hostent * h = ::gethostbyname(name.c_str());
            if (h == 0)
                throw ak::exception() << "::gethostbyname() return " << h;
            unsigned char * ip = (unsigned char *)h->h_addr_list[0];
            std::stringstream ss;
            ss << (int)ip[0] << "." << (int)ip[1] << "." << (int)ip[2] << "." << (int)ip[3];
            win32::wsa::cleanup();
            return ss.str();
        }
    }
}
