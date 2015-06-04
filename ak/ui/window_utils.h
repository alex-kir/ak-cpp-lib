#pragma once
#include <ak/ui/window.h>
#include <vector>
namespace ak
{
    namespace ui
    {
        class window_utils
        {
        public:
            static window from_point(const ak::point<int> & pt);

            static window foreground();
            static window foregroundex();
            static void foreground(const window &);

            static window focus();
            static void focus(const window &);
            static void focusex(const window &);

            static std::vector<window> topwindows();
        };
    }
}