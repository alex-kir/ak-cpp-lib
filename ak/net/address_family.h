#pragma once

#include <ak/enumeration.h>

namespace ak
{
    namespace net
    {
        class address_family : public ak::enumeration
        {
        private:
            address_family(const int val) : ak::enumeration(val) { };
        public:
            const static address_family inet;
        };
    }
}