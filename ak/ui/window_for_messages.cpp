#pragma once
#include <ak/ui/window_for_messages.h>
namespace ak
{
    namespace ui
    {
        void window_for_messages::create()
        {
            window::create<char, int>("Message", "", 0, 0, ak::size<int>(0, 0));
        }
    }
}