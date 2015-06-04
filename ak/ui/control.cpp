#include <ak/ui/control.h>
#include <ak/cast.h>
#include <ak/ui/dc.h>

namespace ak
{
    namespace ui
    {
        //namespace _internal
        //{
        //    //static void set_this(void * h, control * w)
        //    //{
        //    //    SetWindowLongPtrA((HWND)h, GWL_USERDATA, ak::cast<LONG>(w));
        //    //}

        //    //static control * get_this(void * h)
        //    //{
        //    //    return ak::cast<control*>(GetWindowLongPtr((HWND)h, GWL_USERDATA));
        //    //}

        //    static std::map<void*, control*> _map;

        //    static void set_this(void * h, control * w)
        //    {
        //        _map[h] = w;
        //    }

        //    static control * get_this(void * h)
        //    {
        //        if (_map.find(h) == _map.end())
        //            return 0;
        //        return _map[h];
        //    }

        //    LRESULT CALLBACK procedure(HWND h, UINT m, WPARAM w, LPARAM l)
        //    {
        //        //control * This = get_this(h);
        //        //if (This != 0 && This->message(m, w, l))
        //            return 0;

        //        //if (m == WM_PAINT)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_paint(*this_, 0);
        //        //    return 0;
        //        //}
        //        //else if (m == WM_MOUSEMOVE)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_mousemove(*this_, point<int>(LOWORD(l), HIWORD(l)));
        //        //    return 0;
        //        //}
        //        //else if (m == WM_MOUSELEAVE)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_mouseleave(*this_, 0);
        //        //    return 0;
        //        //}
        //        //else if (m == WM_LBUTTONDOWN)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_buttondown(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 1));
        //        //    return 0;
        //        //}
        //        //else if (m == WM_LBUTTONUP)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_buttonup(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 1));
        //        //    return 0;
        //        //}
        //        //else if (m == WM_RBUTTONDOWN)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_buttondown(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 2));
        //        //    return 0;
        //        //}
        //        //else if (m == WM_RBUTTONUP)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_buttonup(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 2));
        //        //    return 0;
        //        //}
        //        //else if (m == WM_MBUTTONDOWN)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_buttondown(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 3));
        //        //    return 0;
        //        //}
        //        //else if (m == WM_MBUTTONUP)
        //        //{
        //        //    control * this_ = get_this(h);
        //        //    this_->wm_buttonup(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 3));
        //        //    return 0;
        //        //}
        //        //else if (m == WM_CLOSE)
        //        //{
        //        //    control::quit();
        //        //    return 0;
        //        //}

        //        return ::DefWindowProc(h, m, w, l);
        //    }
        //}

        control::control()
        { }

        control::~control()
        {
            //_internal::set_this(get_internal_handle(), 0);
        }

        void control::show()
        {
            ::ShowWindow(handle<HWND>(), SW_SHOW);
            ::UpdateWindow(handle<HWND>());
            ::SetForegroundWindow(handle<HWND>());
        }

        void control::show_no_activate()
        {
            ::ShowWindow(handle<HWND>(), SW_SHOWNOACTIVATE);
        }

        void control::hide()
        {
            ::ShowWindow(handle<HWND>(), SW_HIDE);
        }

        bool control::is_show()
        {
            return TRUE == IsWindowVisible(handle<HWND>());
        }

        void control::invalidate()
        {
            ::InvalidateRect(handle<HWND>(), NULL, FALSE);
        }

        int control::post_message(int m, int wparam, int lparam)
        {
            return ::PostMessageA(*this, m, wparam, lparam);
        }

        void control::update_layered(ak::ui::dc & dc)
        {
            RECT rt;
            ::GetWindowRect(handle<HWND>(), &rt);
            SIZE sz = {rt.right - rt.left, rt.bottom - rt.top};
            POINT pt = {0, 0};
            BLENDFUNCTION blender = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
            ::UpdateLayeredWindow(handle<HWND>(), GetDC(0), 0, &sz, dc.object(), &pt, 0, &blender, ULW_ALPHA);
        }

        control control::parent()
        {
            control w;
            w.handle(::GetParent(handle<HWND>()));
            return w;
        }

        BOOL CALLBACK __children(HWND hwnd, LPARAM lparam)
        {
            std::vector<control> * cc = (std::vector<control>*)lparam;
            cc->push_back(control(hwnd));
            return TRUE;
        }

        std::vector<control> control::children()
        {
            std::vector<control> retval;
            BOOL result = ::EnumChildWindows(handle<HWND>(), __children, (LPARAM)&retval);
            return retval;
        }

        ak::rectanglei control::clientrectangle()
        {
            WINDOWINFO wi;
            wi.cbSize = sizeof(wi);
            ::GetWindowInfo(handle<HWND>(), &wi);
            return ak::rectanglei(wi.rcClient.left, wi.rcClient.top, wi.rcClient.right, wi.rcClient.bottom);
        }

        ak::rectangle<int> control::rectangle(bool onscreen)
        {
            if (onscreen)
            {
                RECT rt;
                ::GetWindowRect(handle<HWND>(), &rt);
                return ak::rectanglei(rt.left, rt.top, rt.right, rt.bottom);
            }
            else
            {
                rectanglei rt1 = clientrectangle();
                rectanglei rt2 = parent().clientrectangle();
                return ak::rectanglei(rt1.location() - rt2.location(), rt1.size());
            }
        }

        void control::position(int x, int y)
        {
            ::SetWindowPos(handle<HWND>(), 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER);
        }

        void control::size(int width, int height)
        {
            ::SetWindowPos(handle<HWND>(), 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER);
        }

        void control::rectangle(int x, int y, int width, int height)
        {
            ::SetWindowPos(object<HWND>(), 0, x, y, width, height, SWP_NOOWNERZORDER);
        }

        void control::clientsize(int width, int height)
        {
            RECT rt;
            ::SetRect(&rt, 0, 0, width, height);
            WINDOWINFO wi;
            wi.cbSize = sizeof(wi);
            ::GetWindowInfo(handle<HWND>(), &wi);
            ::AdjustWindowRectEx(&rt, wi.dwStyle, false, wi.dwExStyle);
            size(rt.right - rt.left, rt.bottom - rt.top);
        }

        void control::adjust_size(int cx, int cy)
        {
            WINDOWPLACEMENT wp;
            wp.length = sizeof(wp);
            int right1 = 0;
            int bottom1 = 0;

            HWND wnd = ::GetWindow(handle<HWND>(), GW_CHILD);
            while (wnd)
            {
                ::GetWindowPlacement(wnd, &wp);
                right1 = std::max<int>(right1, wp.rcNormalPosition.right);
                bottom1 = std::max<int>(bottom1, wp.rcNormalPosition.bottom);
                wnd = ::GetWindow(wnd, GW_HWNDNEXT);
            }

            clientsize(right1 + cx, bottom1 + cy);
        }

        void control::adjust_height(int cy)
        {
            WINDOWPLACEMENT wp;
            wp.length = sizeof(wp);
            int bottom1 = 0;

            HWND wnd = ::GetWindow(handle<HWND>(), GW_CHILD);
            while (wnd)
            {
                ::GetWindowPlacement(wnd, &wp);
                bottom1 = std::max<int>(bottom1, wp.rcNormalPosition.bottom);
                wnd = ::GetWindow(wnd, GW_HWNDNEXT);
            }
            sizei sz = size(false);
            clientsize(sz.width, bottom1 + cy);
        }

        std::string control::text()
        {
            int sz = (int)::SendMessageA(handle<HWND>(), (UINT) WM_GETTEXTLENGTH, 0, 0);
            std::string text;
            text.resize(sz + 1);
            ::SendMessageA(handle<HWND>(), (UINT)WM_GETTEXT, sz + 1, (LPARAM)text.c_str());
            text.resize(sz);
            return text;
        }

        void control::text(const std::string & text)
        {
            ::SendMessageA(handle<HWND>(), (UINT)WM_SETTEXT, 0, (LPARAM)text.c_str());
        }

        control control::under_point(const pointi & pt)
        {
            POINT pt1 = { pt.x, pt.y };
            control c1(::WindowFromPoint(pt1));
            pointi pt2 = c1.pointtoclient(pt);
            POINT pt3 = { pt2.x, pt2.y };
            control c2(::RealChildWindowFromPoint(c1.handle<HWND>(), pt3));
            if (!c2.empty())
                return c2;
            return c1;
        }

        pointi control::pointtoclient(const pointi & pt)
        {
            POINT pt1 = { pt.x, pt.y };
            ::ScreenToClient(handle<HWND>(), &pt1);
            return pointi(pt1.x, pt1.y);
        }

        long control::stylemask()
        {
            return ::GetWindowLong(handle<HWND>(), GWL_STYLE);
        }

        long control::stylemaskex()
        {
            return ::GetWindowLong(handle<HWND>(), GWL_EXSTYLE);
        }

        std::string control::classname()
        {
            char buff[1000];
            int n = ::RealGetWindowClassA(handle<HWND>(), buff, 999);
            return std::string(buff, n);
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
//
//void x_Window::topmost(bool b)
//{
//    SetWindowPos(_hWnd, (b)?HWND_TOPMOST:HWND_NOTOPMOST,
//        0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//}

