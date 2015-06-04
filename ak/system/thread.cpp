#include <ak/system/thread.h>
#include <ak/exception.h>

namespace ak
{
    namespace system
    {
        thread::thread(int stack_size)
        {
            _stack_size = stack_size;
            _tid = 0;
            _thread = ::CreateThread(0, _stack_size, (LPTHREAD_START_ROUTINE)run_internal, this, CREATE_SUSPENDED, (LPDWORD)&_tid);
            _stopped = false;
        }

        thread::~thread(void)
        {
            if (!stopped())
                throw ak::exception() << "thread not stopped";
            //terminate();
        }

        void thread::run_internal(thread * th)
        {
            th->procedure();
            th->stop();
        }

        void thread::run()
        {
            if (::ResumeThread(_thread) == (DWORD)-1)
                throw ak::exception() << "::ResumeThread() return (DROWD)-1";
        }

        void thread::terminate()
        {
            ::TerminateThread(_thread, 0);
            _thread = 0;
            _tid = 0;
        }

        void thread::wait()
        {
            ::WaitForSingleObject(_thread, INFINITE);
        }

        void thread::sleep(int interval)
        {
            ::Sleep(interval);
        }

        void thread::sleep(float seconds)
        {
            ::Sleep((int)(seconds * 1000));
        }

        int thread::id()
        {
            return ::GetCurrentThreadId();
        }

        void bg_method::procedure()
        {
            notification_args args;
            args["id"] = id();
            on_thread.notify(args);
        }
    }
}
