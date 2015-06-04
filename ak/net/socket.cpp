#include <ak/net/socket.h>
#include <ak/net/socket_address.h>
#include <ak/exception.h>

namespace ak
{
    namespace net
    {
        void socket::connect(const std::string & host, int port)
        {
            if (is_connected())
                throw ak::exception() << "already connected";
 
            int s = (int)::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (s == INVALID_SOCKET)
                throw ak::exception() << "::socket() return INVALID_SOCKET";

            ak::net::socket_address ca(ak::net::address_family::inet, host, port);

            if (::connect(s, (SOCKADDR*)ca.ptr(), ca.size()) == SOCKET_ERROR)
            {
                ::closesocket(s);
                throw ak::exception() << "::connect() return SOCKET_ERROR";
            }
            _socket = s;
        }

        int socket::write(const void * data, size_t length)
        {
            int n = ::send(_socket, (const char*)data, (int)length, 0);
            if (n == SOCKET_ERROR)
                throw ak::exception() << "::send() return SOCKET_ERROR";
            return n;
        }

        int socket::read(void * data, size_t length)
        {
            int n = ::recv(_socket, (char*)data, (int)length, 0);
            if (n == SOCKET_ERROR)
                throw ak::exception() << "::recv() return SOCKET_ERROR";
            if (n == 0)
                close();
            return n;
        }
        
        void socket::read_all(void * data, size_t length)
        {
            do
            {
                int n = read(data, length);
                length -= n;
                data = ((char*)data) + n;
            }while(length && is_connected());

            if (length && !is_connected())
            {
                throw ak::exception() << "socket::read_all() : socket closed before all data will read";
            }
        }
    }
}
//
//namespace ak
//{
//    namespace net
//    {
//        bool socket_accepter::select(float seconds)
//        {
//            throw ak::exception() << "socket_accepter::select() not implemented";
//        }
//
//        void socket_accepter::bind(const std::string & host, int port)
//        {
//			int s = (int)::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//            if (s == INVALID_SOCKET)
//                throw ak::exception() << "::socket() return INVALID_SOCKET";
//
//            ak::net::socket_address sa(ak::net::address_family::inet, host, port);
//
//            if (::bind(s, (SOCKADDR*)sa.ptr(), sa.size()) == SOCKET_ERROR)
//            {
//                ::closesocket(s);
//                throw ak::exception() << "::bind() return SOCKET_ERROR";
//            }
//            if (::listen(s, 1) == SOCKET_ERROR)
//            {
//                ::closesocket(s);
//                throw ak::exception() << "::listen() return SOCKET_ERROR";
//            }
//            _socket = s;
//        }
//
//        void socket_accepter::accept(socket & sock)
//        {
//            if (sock.is_connected())
//                throw ak::exception() << "socket_accepter::accept() : input socket already connected.";
//            if (!is_connected())
//                throw ak::exception() << "socket_accepter::accept() : socket is not connected.";
//
//            int s = (int)::accept(_socket, NULL, NULL);
//            if (s == SOCKET_ERROR)
//                throw ak::exception() << "::accept() return SOCKET_ERROR";
//
//            sock._socket = s;
//        }
//
//    }
//}

namespace ak
{
    namespace net
    {
//        socket::socket(void)
//        {
//            system::wsa::startup();
//            _socket = INVALID_SOCKET;
//            _is_server = false;
//        }
//
//        socket::~socket(void)
//        {
//            close();
//            system::wsa::cleanup();
//        }
//
//        void socket::connect(const std::string & host, int port)
//        {
//            close();
// 
//            int s = (int)::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//            if (s == INVALID_SOCKET)
//                throw ak::exception() << "::socket() return " << _socket;
//
//            socket_address client_addr(address_family::inet, host, port);
//
//            if (::connect(s, (SOCKADDR*)client_addr.ptr(), client_addr.size()) == SOCKET_ERROR)
//            {
//                ::closesocket(s);
//                throw ak::exception() << "connect() return SOCKET_ERROR";
//            }
//            _socket = s;
//        }
//
//        void socket::bind(const std::string & host, int port)
//        {
//			int s = (int)::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//            if (s == INVALID_SOCKET)
//            {
//                throw ak::exception() << "socket() return " << s;
//            }
//            sockaddr_in service;
//            service.sin_family = AF_INET;
//            service.sin_addr.s_addr = inet_addr(host.c_str());
//            service.sin_port = htons(port);
//			if (::bind(s, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
//            {
//                ::closesocket(s);
//                throw ak::exception() << "bind() return FALSE";
//            }
//            if (listen( s, 1) == SOCKET_ERROR)
//            {
//                ::closesocket(s);
//                throw ak::exception() << "listen() return SOCKET_ERROR";
//            }
//            _is_server = true;
//            _socket = s;
//        }
//
//        void socket::accept(ak::net::socket & sock)
//        {
//            if (sock.is_connected())
//                throw ak::exception() << "input socket already connected.";
//
//			int s = (int)::accept( _socket, NULL, NULL );
//            if (s == SOCKET_ERROR)
//                throw ak::exception() << "::accept() return SOCKET_ERROR";
//
//            sock._socket = s;
//        }
//
//        int socket::send(const void * data, size_t length)
//        {
//			int sent_count = ::send(_socket, (const char*)data, (int)length, 0);
//            if (sent_count == SOCKET_ERROR)
//                throw ak::exception() << "send() return SOCKET_ERROR";
//            return sent_count;
//        }
//
//        int socket::recv(void * data, size_t length)
//        {
//			int n = ::recv(_socket, (char*)data, (int)length, 0);
//            if (n == SOCKET_ERROR)
//                throw ak::exception() << "recv() return SOCKET_ERROR";
//            if (n == 0)
//                close();
//            return n;
//        }
//
//        void socket::recv_full(void * data, size_t length)
//        {
//            do
//            {
//                int n = recv(data, length);
//                length -= n;
//                data = ((char*)data) + n;
//            }while(length && is_connected());
//        }
//
//        void socket::close()
//        {
//            ::closesocket(_socket);
//            _socket = INVALID_SOCKET;
//        }
//
//        std::vector<socket*> socket::select(const std::vector<socket*> & socks, int interval)
//        {
//            timeval tv;
//            if (interval >= 0)
//            {
//                tv.tv_sec = interval / 1000;
//                tv.tv_usec = interval % 1000;
//            }
//
//            fd_set fdr;
//            FD_ZERO(&fdr);
//            for (size_t i = 0; i < socks.size(); i++)
//            {
//                FD_SET(socks[i]->_socket, &fdr);
//            }
//
//			::select(0, &fdr, 0, 0, (interval >= 0) ? &tv : 0);
//
//            std::vector<socket*> retval;
//            for (size_t i = 0; i < socks.size(); i++)
//            {
//                if (FD_ISSET(socks[i]->_socket, &fdr))
//                    retval.push_back(socks[i]);
//            }
//
//            return retval;
//        }
//
//        bool socket::is_connected()
//        {
//            return _socket != 0 && _socket != -1;
//        }
//
//        bool socket::select(int interval)
//        {
//            std::vector<socket*> ss;
//            ss.push_back(this);
//            return select(ss, interval).size() == 1;
//        }
//
        text_writer & text_writer::operator << (const std::string & str)
        {
            //std::cout << str;
            _socket.send(str.c_str(), str.size());
            return *this;
        }

        text_writer & text_writer::operator << (const char * str)
        {
            //std::cout << str;
            _socket.send(str, strlen(str));
            return *this;
        }

        void text_reader::getline(std::string & str, char stop)
        {
            readline(str, stop);
        }

        void text_reader::readline(std::string & str, char stop)
        {
            str.clear();
            while(_socket.is_connected() && _socket.select(30000))
            {
                char c = stop;
                int n = _socket.recv(&c, 1);
                if (c == stop)
                    break;
                str += c;
            }
        }

    }
}