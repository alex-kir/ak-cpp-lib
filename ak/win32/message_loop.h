#pragma once

namespace ak
{
    namespace win32
    {
        class message_loop
        {
            int threadid;
        public:
            message_loop();
            void run() { start(); }
            void start();
            void stop();
        };
    }
}