#include <ak/net/basic_socket.h>
#include <ak/net/get_last_error.h>
#include <ak/exception.h>
#include <sstream>


namespace ak
{
    namespace net
    {
		int infinite = INFINITE;

        basic_socket::basic_socket()
        {
            ak::win32::wsa::startup();
            _socket = 0;
        }
        basic_socket::basic_socket(const address_family & af, const socket_type & type, const socket_protocol & protocol)
        {
            ak::win32::wsa::startup();
            _socket = ::socket(af, type, protocol);
        }

        basic_socket::~basic_socket(void)
        {
            close();
            ak::win32::wsa::cleanup();
        }

        bool basic_socket::is_connected()
        {
            return _socket != 0 && _socket != -1 && _socket != (~0);
        }

        void basic_socket::close()
        {
            if (is_connected())
            {
                ::closesocket(_socket);
                _socket = 0;
            }
        }

        bool basic_socket::select(float seconds)
        {
            timeval tv;
            tv.tv_sec = (int)seconds;
            tv.tv_usec = ((int)(seconds * 1000)) % 1000;

            fd_set fdread;
            FD_ZERO(&fdread);
            FD_SET(_socket, &fdread);

			::select(0, &fdread, 0, 0, &tv);

            return FD_ISSET(_socket, &fdread) != 0;
        }

        int basic_socket::get_option(const socket_option & so)
        {
            int retval;
            int err = ::setsockopt(_socket, SOL_SOCKET, so, (char*)&retval, sizeof(retval));
            if (err != 0)
                throw ak::exception() << "::setsockopt() returns " << err << " " << net::get_last_error();
            return retval;
        }

        void basic_socket::set_option(const socket_option & so, int val)
        {
            int err = ::setsockopt(_socket, SOL_SOCKET, so, (char*)&val, sizeof(val));
            if (err != 0)
                throw ak::exception() << "::setsockopt() returns " << err << " " << net::get_last_error();
        }
    }
}