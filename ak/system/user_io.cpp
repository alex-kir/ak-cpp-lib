#include <ak/system/user_io.h>
namespace ak
{
    namespace system
    {
        point<int> user_io::cursor_position()
        {
            POINT pt;
            ::GetCursorPos(&pt);
            return point<int>(pt.x, pt.y);
        }

        bool user_io::is_cursor_I_beem()
        {
            CURSORINFO ci;
            ci.cbSize = sizeof(ci);
            ::GetCursorInfo(&ci);
            HCURSOR hIbeam = ::LoadCursor(0, IDC_IBEAM);
            return ci.hCursor == hIbeam;
        }

        point<int> user_io::caret_position()
        {
            POINT pt;
            ::GetCaretPos(&pt);
            return point<int>(pt.x, pt.y);
        }

        bool user_io::key_state(virtual_key vk)
        {
            int flag = ::GetAsyncKeyState(vk);
            return (flag & 0x8000) == 0x8000;
        }

        void user_io::key_state(virtual_key vk, int flags)
        {
            INPUT inp;
            inp.type = INPUT_KEYBOARD;
            inp.ki.wVk = vk;
            inp.ki.dwFlags = flags;
            inp.ki.time = 0;
            inp.ki.dwExtraInfo = 0;
            ::SendInput(1, &inp, sizeof(INPUT));
        }

        void user_io::key_down(int vk)
        {
            INPUT inp;
            inp.type = INPUT_KEYBOARD;
            inp.ki.wVk = vk;
            inp.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
            inp.ki.time = 0;
            inp.ki.dwExtraInfo = 0;
            ::SendInput(1, &inp, sizeof(INPUT));
        }

        void user_io::key_up(int vk)
        {
            INPUT inp;
            inp.type = INPUT_KEYBOARD;
            inp.ki.wVk = vk;
            inp.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
            inp.ki.time = 0;
            inp.ki.dwExtraInfo = 0;
            ::SendInput(1, &inp, sizeof(INPUT));
        }

        void user_io::key_down_sc(int sc)
        {
            INPUT inp;
            inp.type = INPUT_KEYBOARD;
            inp.ki.wScan = sc;
            inp.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_SCANCODE;
            inp.ki.time = 0;
            inp.ki.dwExtraInfo = 0;
            ::SendInput(1, &inp, sizeof(INPUT));
        }

        void user_io::key_up_sc(int sc)
        {
            INPUT inp;
            inp.type = INPUT_KEYBOARD;
            inp.ki.wScan = sc;
            inp.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
            inp.ki.time = 0;
            inp.ki.dwExtraInfo = 0;
            ::SendInput(1, &inp, sizeof(INPUT));
        }

        void user_io::key_type(char ch)
        {
            virtual_key vk = ::VkKeyScanA(ch);
            key_type(vk);
            //int sc = ::OemKeyScan(ch);
            //key_down_sc(sc);
            //key_up_sc(sc);
        }
    }
}