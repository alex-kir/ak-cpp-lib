#pragma once
#include <ak/system/handle.h>

namespace ak
{
    namespace system
    {
        class handle_rw : public handle
        {
        public:
			handle_rw()
			{ }

			//handle_rw(const handle_rw & h) : handle(h)
			//{ }

			//handle_rw(const handle & h) : handle(h)
			//{ }

            int read(void * b, int l);
            int write(const void * b, int l);
            void write_eof();
            void timeouts(int interval);
            int timeouts();
        };
    }
}