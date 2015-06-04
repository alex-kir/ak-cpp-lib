#pragma once

#include <string>

#include <ak/net/address_family.h>
#include <ak/net/socket_type.h>
#include <ak/net/socket_protocol.h>
#include <ak/net/socket_option.h>
#include <ak/misc/nocopy.h>

namespace ak
{
    namespace net
    { 
        extern int infinite;

        class basic_socket : public ak::misc::nocopy
        {
        protected:
            int _socket;
            basic_socket();
            basic_socket(const address_family & af, const socket_type & type, const socket_protocol & protocol);
            ~basic_socket(void);
        public:
            bool is_connected();
            void close();
            bool select(float seconds);


            int get_option(const socket_option & so);
            void set_option(const socket_option & so, int val);
        };
    }
}