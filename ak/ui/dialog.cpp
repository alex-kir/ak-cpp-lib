#include <ak/ui/dialog.h>
#include <ak/cast.h>
#include <ak/ui/dc.h>

namespace ak
{
    namespace ui
    {
        namespace _dialog_internal
        {
            std::map<int, dialog_result> _commands;
            void * g_dialog_proc_a = 0;
            void * dialog_proc_a()
            {
                if (g_dialog_proc_a == 0)
                {
                    WNDCLASSEXA wcx;
                    GetClassInfoExA(::GetModuleHandleA(0), "#32770", &wcx);
                    g_dialog_proc_a = wcx.lpfnWndProc;
                }
                return g_dialog_proc_a;
            }

            void set_command(const dialog_result & cmd)
            {
                _commands[::GetCurrentThreadId()] = cmd;
            }

            const dialog_result & get_command()
            {
                return _commands[::GetCurrentThreadId()];
            }

            LRESULT CALLBACK procedure1(HWND h, UINT m, WPARAM w, LPARAM l)
            {
                if (false) { }
                else if (WM_CLOSE == m)
                {
                    set_command(dialog_result::close());
                }
                else if (WM_QUERYENDSESSION == m)
                {
                    set_command(dialog_result::queryendsession());
                }
                else if (WM_COMMAND == m)
                {
                    int c = HIWORD(w);
                    if (false) { }
                    else if (BN_CLICKED == c)
                    {
                        set_command(dialog_result::button_clicked(window(l).get_id()));
                    }
                    else
                        return ::CallWindowProcA((WNDPROC)dialog_proc_a(), h, m, w, l);
                }
                else
                    return ::CallWindowProcA((WNDPROC)dialog_proc_a(), h, m, w, l);
                return 0;
            }

            void _track_mouse_events(void * h)
            {
                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof(tme);
                tme.dwFlags = TME_LEAVE;
                tme.dwHoverTime = 50;
                tme.hwndTrack = (HWND)h;
                ::TrackMouseEvent(&tme);
            }

            LRESULT CALLBACK procedure(HWND h, UINT m, WPARAM w, LPARAM l)
            {
                if (false) { }
                else if (WM_CLOSE == m)
                {
                    set_command(dialog_result::close());
                }
                else if (WM_QUERYENDSESSION == m)
                {
                    set_command(dialog_result::queryendsession());
                }
                else if (WM_MOUSEMOVE == m)
                {
                    set_command(dialog_result::mouse_move());
                    _track_mouse_events(h);
                }
                else if (WM_MOUSELEAVE == m)
                {
                    set_command(dialog_result::mouse_leave());
                }
                else if (WM_TIMER == m)
                {
                    set_command(dialog_result::timer((int)w));
                }
                else if (WM_COMMAND == m)
                {
                    int c = HIWORD(w);
                    if (false) { }
                    else if (BN_CLICKED == c)
                    {
                        set_command(dialog_result::button_clicked(window(l).get_id()));
                    }
                    else
                        return ::CallWindowProcA((WNDPROC)dialog_proc_a(), h, m, w, l);
                }
                return ::CallWindowProcA((WNDPROC)dialog_proc_a(), h, m, w, l);
            }
        }

        void dialog::create_toolwnd(const std::string & title, const ak::size<int> & sz)
        {
            unsigned int ws = 
                WS_CAPTION        |
                WS_SYSMENU        |
                0;

            unsigned int wsex = 
                //WS_EX_TOPMOST    |
                WS_EX_TOOLWINDOW  |
                0;

            window::create<char, int>("#32770", title, ws, wsex, sz);
            ::SetWindowLongA((HWND)get_internal_handle(), GWL_WNDPROC, ak::cast_ri<LONG>(_dialog_internal::procedure));
        }

        void dialog::create_layred(const ak::rectangle<int> & rect)
        {
            unsigned int ws = 
                WS_POPUP            |
                0;

            unsigned int wsex = 
                WS_EX_TOPMOST       |
                WS_EX_TOOLWINDOW    |
                WS_EX_LAYERED       |
                0;

            window::create<char, int>("#32770", "", ws, wsex, rect);
            ::SetWindowLongA((HWND)get_internal_handle(), GWL_WNDPROC, ak::cast_ri<LONG>(_dialog_internal::procedure));
        }

        const dialog_result & dialog::show_dialog(bool auto_show)
        {
            if (auto_show)
                show();
            _dialog_internal::set_command(dialog_result::unknown());
            MSG msg;
            while (::GetMessageA(&msg, 0, 0, 0))
            {
                ::TranslateMessage(&msg); 
                ::DispatchMessage(&msg);
                const dialog_result & r = _dialog_internal::get_command();
                if (r != dialog_result::unknown())
                    return r;
            }
            return _dialog_internal::get_command();
        }
    }
}


//LRESULT CALLBACK x_Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    x_Window * _this = get_this(hWnd);
//    if (_this)
//    {
//        if (uMsg == WM_CLOSE)
//            return _this->_onClose();
//        else if (uMsg == WM_TIMER)
//            return _this->_onTimer();
//        //        else if (uMsg == WM_LBUTTONDBLCLK)
//        //            return _this->_onDblClick();
//        else if (uMsg == WM_COMMAND)
//        {
//            int c = HIWORD(wParam);
//            if (c == BN_CLICKED)
//            {
//                x_Window * child = get_this((HWND)lParam);
//                if (child)
//                    child->_onClick();
//            }
//            else if (c == LBN_SELCHANGE)
//            {
//                x_Window * child = get_this((HWND)lParam);
//                if (child)
//                    child->_onSelChange();
//            }
//            else if (c == LBN_DBLCLK)
//            {
//                x_Window * child = get_this((HWND)lParam);
//                if (child)
//                    child->_onDblClick();
//            }
//            else
//                int asdfasdf=0;
//        }
//        else if (uMsg == WM_NOTIFY)
//        {
//            NMHDR * hdr = (NMHDR *)lParam;
//            if (hdr->code == TCN_SELCHANGE)
//            {
//                x_Window * child = get_this(hdr->hwndFrom);
//                if (child)
//                {
//                    child->_onTabchange();
//                }
//            }
//
//        }
//
//        if (x_Window::WindowProc != _this->_fnPrevProc && _this->_fnPrevProc != 0)
//        {
//            return CallWindowProc(_this->_fnPrevProc, hWnd, uMsg, wParam, lParam);
//        }
//    }
//
//    return DefWindowProc(hWnd, uMsg, wParam, lParam);
//}
//
//x_Window::x_Window(const x_Window * prnt, const char * title, const char * clname, int x, int y, int width, int height, int st, int stex)
//{
//
//#ifndef _DEBUG
//    st = st & (st ^ WS_BORDER);
//#endif // _DEBUG
//
//    _fnPrevProc = NULL;
//
//    WNDCLASSEX wcx;
//    if (!GetClassInfoEx(GetModuleHandle(0), clname, &wcx))
//    {
//        wcx.cbSize = sizeof(wcx);
//        wcx.style = CS_HREDRAW | CS_VREDRAW;
//        wcx.lpfnWndProc = WindowProc;
//        wcx.cbClsExtra = 0;
//        wcx.cbWndExtra = 0;
//        wcx.hInstance = GetModuleHandle(0);
//        wcx.hIcon = NULL;
//        wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
//        wcx.hbrBackground = (HBRUSH)COLOR_WINDOW;
//        wcx.lpszMenuName = NULL;
//        wcx.lpszClassName = clname;
//        wcx.hIconSm = NULL; 
//        RegisterClassEx(&wcx);
//    }
//
//    _hWnd = CreateWindowExA(stex, clname, title,
//        st, 
//        x, y, width, height,
//        (prnt)?prnt->_hWnd:NULL, NULL, GetModuleHandle(0), (LPVOID)this);
//
//    if (_hWnd)
//    {
//        set_this(_hWnd, this);
//        _fnPrevProc = (WNDPROC)SetWindowLongPtr(_hWnd, GWL_WNDPROC, (LONG)WindowProc);
//    }
//}
//
//x_Window::~x_Window()
//{
//    //DestroyWindow(_hWnd);
//};
//
//void x_Window::show(bool sh)
//{
//    ShowWindow(_hWnd, sh?SW_SHOW:SW_HIDE);
//}
//
//int x_Window::gettext(char * buff, int sz)
//{
//    return (int)SendMessageA(_hWnd, (UINT) WM_GETTEXT, sz, (LPARAM)buff);
//}
//
//bool x_Window::settext(const char * buff)
//{
//    return TRUE == SendMessageA(_hWnd, (UINT) WM_SETTEXT, 0, (LPARAM)buff);
//}
//
//int x_Window::get_id()
//{
//    return GetWindowLong(_hWnd, GWL_ID);
//}
//
//void x_Window::set_id(int id)
//{
//    SetWindowLong(_hWnd, GWL_ID, id);
//}
//
//void x_Window::settimer(int id, int elapse)
//{
//    SetTimer(_hWnd, id, elapse, NULL);
//}
//
//void x_Window::killtimer(int id)
//{
//    KillTimer(_hWnd, id);
//}
//
//void x_Window::topmost(bool b)
//{
//    SetWindowPos(_hWnd, (b)?HWND_TOPMOST:HWND_NOTOPMOST,
//        0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//}

