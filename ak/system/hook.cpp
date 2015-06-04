
#include <ak/system/hook.h>
#include <ak/system/thread.h>
#include <ak/system/module.h>

namespace ak
{
    namespace system
    {
        void hook::create_keyboard_ll_global(proc pfn)
        {
            ::SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)pfn, 0, ak::system::thread::id());
        }

        void hook::create_keyboard_ll_hook(const std::string & dllname, const std::string & procname)
        {
            module dll = module::get_or_load(dllname);
            HOOKPROC proc = dll.getproc<HOOKPROC>(procname);
            ::SetWindowsHookEx(WH_KEYBOARD_LL, proc, dll.object<HMODULE>(), 0);
        }

        void hook::create_keyboard_hook(const std::string & dllname, const std::string & procname)
        {
            module dll = module::get_or_load(dllname);
            HOOKPROC proc = dll.getproc<HOOKPROC>(procname);
            ::SetWindowsHookEx(WH_KEYBOARD, proc, dll, 0);
        }


        int hook::call_next(int code, int wparam, int lparam)
        {
            return (int)::CallNextHookEx(0, code, wparam, lparam);
        }
    }
}