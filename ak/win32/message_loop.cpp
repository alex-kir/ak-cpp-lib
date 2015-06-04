#pragma once
#include <ak/win32/message_loop.h>
#include <ak/system/thread.h>
namespace ak
{
    namespace win32
    {
        message_loop::message_loop()
        {
            threadid = 0;
        }

        void message_loop::start()
        {
            if (threadid != 0 && threadid != ak::system::thread::id())
                throw ak::exception() << "message_loop already used in another thread";
            threadid = ak::system::thread::id();
            MSG msg;
            while (GetMessage(&msg, 0, 0, 0) && msg.message != WM_QUIT)
            {
                DispatchMessageA(&msg);
                TranslateMessage(&msg);
            }
            threadid = 0;
        }

        void message_loop::stop()
        {
            ::PostThreadMessage(threadid, WM_QUIT, 0, 0);
            //::PostQuitMessage(0);
        }
    }
}