#pragma once

#include <ak/misc/nocopy.h>

namespace ak
{
    namespace system
    {
        class mutex : misc::nocopy
        {
        public:
            class locker
            {
            public:
                mutex::locker(mutex & mutex) : _mutex(mutex)
                {
                    _mutex.wait();
                }

                mutex::locker::~locker()
                {
                    _mutex.release();
                }
            private:
                mutex & _mutex;
            };
        public:
            mutex(bool lock = false);
            ~mutex(void);
            bool wait(int interval = 0xffffffff);
            void release();
        private:
            void * _mutex;
        };
    }
}