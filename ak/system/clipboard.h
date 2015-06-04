#pragma once
#include <string>
#include <ak/ui/window.h>
namespace ak
{
    namespace system
    {
        class clipboard
        {
        public:
            static void copy(const ak::ui::window & w);
            static std::string text();
            static std::wstring wtext();
            static void wtext(const std::wstring & text);
            static void clear();
            static void test();
        };
    }
}