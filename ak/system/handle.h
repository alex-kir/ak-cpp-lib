#pragma once

#include <ak/misc/nocopy.h>

namespace ak
{
    namespace system
    {
        class handle : public ak::misc::nocopy
        {
        protected:
            void * _handle;
        public:
            handle() : ak::misc::nocopy(), _handle(0) { }
        public:
            virtual ~handle() { }
        public:
            inline void * internal_handle() const { return _handle; }
            inline void internal_handle(void * h){ _handle = h; }
        public:
            void close();
            void duplicate_to(handle & h) const;
            bool is_valid_handle() const;
            bool wait(int interval) const;
        };
    }
}