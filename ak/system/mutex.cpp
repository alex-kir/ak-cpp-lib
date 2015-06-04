#include <ak/system/mutex.h>
#include <ak/exception.h>
#include <windows.h>
namespace ak
{
    namespace system
    {
        mutex::mutex(bool lock)
        {
            _mutex = ::CreateMutex(0, lock, 0);
        }

        mutex::~mutex(void)
        {
            ::CloseHandle(_mutex);
        }

        bool mutex::wait(int interval)
        {
            if (interval == 0)
                interval = 1;
            DWORD state = ::WaitForSingleObject(_mutex, interval/*INFINITE*/);
            if (state == WAIT_TIMEOUT)
            {
                return false;
            }
            else if (state == WAIT_ABANDONED)
            {
                // todo:
            }
            if (state == WAIT_OBJECT_0)
            {
                return true;
            }
            throw ak::exception() << "mutex::wait() : state = " << state;
        }

        void mutex::release()
        {
            ::ReleaseMutex(_mutex);
        }
    }
}