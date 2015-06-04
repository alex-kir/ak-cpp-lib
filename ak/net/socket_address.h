#pragma once

#include <ak/net/address_family.h>
#include <vector>

namespace ak
{
    namespace net
    {
        class socket_address
        {
        private:
            typedef unsigned char byte;
        public:
            socket_address(const address_family & family, const std::string & host, int port);
            socket_address(const std::string & host, int port);
            socket_address(unsigned int host, int port);
            socket_address(int port);
            socket_address();
        public:
            void reset(void * data, int len);
        public:
            std::string location() const;
            std::string host() const;
            int port() const;
        public:
            const void * ptr() const { return &_cdata[0]; };
            const int size() const { return (int)_cdata.size(); };
        public:
            static std::string name2ip(const std::string & name);
        private:
            std::vector<byte> _cdata;
        };
    }
}