#pragma once

#include <ak/misc/nocopy.h>

namespace ak
{
    namespace system
    {
        class handle_holder : public ak::misc::nocopy
        {
        private:
            void * _h;
        public:
            handle_holder(void * h);
            virtual ~handle_holder();
            void * get() { return _h; }
        };
    }
}