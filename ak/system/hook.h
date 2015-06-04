#pragma once 

#include <string>

namespace ak
{
    namespace system
    {
        class hook
        {
        public:
            typedef int (__stdcall * proc)(int code, int wParam, int lParam);
        public:
            static void create_keyboard_ll_global(proc pfn);
            static void create_keyboard_ll_hook(const std::string & dllname, const std::string & procname);
            static void create_keyboard_hook(const std::string & dllname, const std::string & procname);

            static int call_next(int code, int wparam, int lparam);
        };
    }
}