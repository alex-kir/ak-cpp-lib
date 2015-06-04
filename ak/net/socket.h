#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <ak/net/basic_socket.h>

namespace ak
{
    namespace net
    {
        class socket : public basic_socket
        {
            friend class socket_accepter;
        public:
            void connect(const std::string & host, int port);

            int write(const void * data, size_t length);
            int read(void * data, size_t length);
            void read_all(void * data, size_t length);

            inline int send(const void * data, size_t length) { return write(data, length); };
            inline int recv(void * data, size_t length) { return read(data, length); };
        };
    }
}

namespace ak
{
    namespace net
    {
		extern int infinite;

        class text_writer
        {
            socket & _socket;
        public:
            text_writer(socket & s) : _socket(s)
            { }

            text_writer & operator << (const std::string & str);
            text_writer & operator << (const char * str);

            template<typename T>
            text_writer & operator << (T t)
            {
                std::stringstream ss;
                ss << t;
                *this << ss.str();
                return *this;
            }
        };
            
        class text_reader
        {
            socket & _socket;
        public:
            text_reader(socket & s) : _socket(s)
            { }

            void getline(std::string & str, char stop = '\n');
            void readline(std::string & str, char stop = '\n');
        };
    }
}