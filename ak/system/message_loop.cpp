#pragma once
#include <ak/ui/messagebox.h>
namespace ak
{
    namespace system
    {
        void message_loop()
        {
            MSG msg;
            while (GetMessage(&msg, 0, 0, 0))
            {
                DispatchMessageA(&msg);
                TranslateMessage(&msg);
            }
        }
    }
}