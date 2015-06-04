#pragma once
#include <ak/ui/window_utils.h>
#include <ak/types/types.h>
namespace ak
{
    namespace ui
    {
        window window_utils::from_point(const ak::point<int> & pt)
        {
            POINT point;
            point.x = pt.x;
            point.y = pt.y;
            return window(::WindowFromPoint(point));
        }

        window window_utils::foreground()
        {
            return window(::GetForegroundWindow());
        }

        window window_utils::foregroundex()
        {
            ak::types::pointi pc = ak::system::user_io::caret_position();
            HWND w1 = ::GetForegroundWindow();

            DWORD tid1 = ::GetCurrentThreadId();
            DWORD tid2 = ::GetWindowThreadProcessId(w1, NULL);
            BOOL b1 = ::AttachThreadInput(tid1, tid2, TRUE);
            if (b1)
            {
                GUITHREADINFO gti2;
                gti2.cbSize = sizeof(gti2);
                BOOL b2 = ::GetGUIThreadInfo(tid2, &gti2);
                if (b2)
                {
                    if (gti2.hwndFocus != 0)
                        w1 = gti2.hwndFocus;
                }
                //BOOL b3 = ::AttachThreadInput(tid1, tid2, FALSE);
            }

            return window(w1);
        }

        void window_utils::foreground(const window & w)
        {
            ::SetForegroundWindow(w.object<HWND>());
        }

        window window_utils::focus()
        {
            window w;
            w.object<HWND>(::GetFocus());
            return w;
        }

        void window_utils::focus(const window & w)
        {
            ::SetFocus(w.object<HWND>());
        }

        void window_utils::focusex(const window & w)
        {
            DWORD tid1 = ::GetCurrentThreadId();
            DWORD tid2 = ::GetWindowThreadProcessId((HWND)w.get_internal_handle(), NULL);
            BOOL b1 = ::AttachThreadInput(tid1, tid2, TRUE);
            if (b1)
            {
                ::SetFocus(w.object<HWND>());
                BOOL b3 = ::AttachThreadInput(tid1, tid2, FALSE);
            }
        }

        BOOL lpEnumFunc(HWND hwnd, LPARAM lparam)
        {
            std::vector<window> * windows = (std::vector<window>*)lparam;
            windows->push_back(window(hwnd));
            return TRUE;
        }

        std::vector<window> window_utils::topwindows()
        {
            std::vector<window> retval;
            BOOL result = ::EnumWindows((WNDENUMPROC)lpEnumFunc, (LPARAM)&retval);
            return retval;
        }
    }
}
