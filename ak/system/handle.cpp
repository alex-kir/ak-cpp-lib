#include <ak/system/handle.h>

#include <ak/system/win32.h>
#include <ak/exception.h>

namespace ak
{
    namespace system
    {
        void handle::close()
        {
            ::CloseHandle(_handle);
            _handle = 0;
        }

        void handle::duplicate_to(handle & h) const
        {
            void * dup = 0;
            BOOL b = DuplicateHandle(GetCurrentProcess(), _handle,
                GetCurrentProcess(), &dup, 0,
                FALSE, DUPLICATE_SAME_ACCESS);
            if (b != 0)
                throw ak::exception() << "DuplicateHandle() return FALSE";
            h.internal_handle(dup);
        }

        bool handle::is_valid_handle() const
        {
            return _handle != 0 && _handle != (void*)-1;
        }

        bool handle::wait(int interval) const
        {
            DWORD res = ::WaitForSingleObject(internal_handle(), interval);
            if (res == WAIT_TIMEOUT)
                return false;
            else if (res == WAIT_OBJECT_0) 
                return true;
            else
                throw ak::exception() << std::hex << res << " " << ak::system::get_last_error();
        }
    }
}