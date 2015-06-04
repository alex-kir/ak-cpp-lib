#include <ak/system/handle_rw.h>
#include <ak/system/get_last_error.h>
#include <ak/system/win32.h>

#include <ak/exception.h>
#include <iostream>

namespace ak
{
    namespace system
    {
        int handle_rw::read(void * b, int l)
        {
            DWORD r = 0;
            if (!is_valid_handle())
                throw ak::exception() << "handle is not valid";

            //OVERLAPPED over;
            //memset(&over, 0, sizeof(OVERLAPPED));
            //over.hEvent = CreateEventA(0, false, true, 0);

            //if (!ReadFileEx(get(), b, l, /*&r,*/ &over, 0))
            //    return 0;
            //std::cout << std::endl << "win32::ReadFile(), " << get_last_error();

            //::WaitForSingleObject(over.hEvent, 1000);
            //r = over.Offset;
            if (!ReadFile(internal_handle(), b, l, &r, 0))
                throw ak::exception() << "win32::ReadFile(), " << get_last_error();
            return r;
        }

        int handle_rw::write(const void * b, int l)
        {
            DWORD w = 0;
            if (!is_valid_handle())
                throw ak::exception() << "handle is not valid";

            if (!WriteFile(internal_handle(), b, l, &w, 0))
                throw ak::exception() << "win32::WriteFile(), " << get_last_error();

            return w;
        }

        void handle_rw::write_eof()
        {
            if (!is_valid_handle())
                throw ak::exception() << "handle is not valid";

            if (!::SetEndOfFile(internal_handle()))
                throw ak::exception() << "win32::SetEndOfFile(), " << get_last_error();
        }

        void handle_rw::timeouts(int interval)
        {
            COMMTIMEOUTS ct;
            ::GetCommTimeouts(internal_handle(), &ct);
            ct.ReadIntervalTimeout = interval;
            ::SetCommTimeouts(internal_handle(), &ct);
        }

        int handle_rw::timeouts()
        {
            COMMTIMEOUTS ct;
            ::GetCommTimeouts(internal_handle(), &ct);
            return ct.ReadIntervalTimeout;
        }
    }
}