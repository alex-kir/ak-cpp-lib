#pragma once
#include <ak/sysobj.h>
#include <ak/notification.h>

namespace ak
{
    namespace system
    {
        class thread
        {
            void * _thread;
            static void run_internal(thread * th);
        protected:
            int _tid;
            int _stack_size;
            thread(int stack_size = 2 * 1024 * 1024);
            virtual void procedure() = 0;
            bool _stopped;
            virtual ~thread(void);
        public:

            void run();
            void start() { run(); }
            void pause();
            void stop() { _stopped = true; };
            bool stopped() { return _stopped; };
            void terminate();
            void wait();

        public:
            static void sleep(int interval);
            static void sleep(float seconds);
            static int id();
        };

        class bg_method : public thread
        {
            notifications on_thread;
            virtual void procedure();
            
        public:
            template<typename _Class, typename _Method>
            void create(_Class * object, _Method method, bool create_and_start)
            {
                on_thread.add(object, method);
                if (create_and_start)
                    start();
            }
        };

    }
}
