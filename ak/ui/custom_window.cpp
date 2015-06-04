#include <ak/ui/window.h>
#include <ak/cast.h>
#include <ak/ui/dc.h>

namespace ak
{
    namespace ui
    {
        namespace _internal
        {
            //static void set_this(void * h, window * w)
            //{
            //    SetWindowLongPtrA((HWND)h, GWL_USERDATA, ak::cast<LONG>(w));
            //}

            //static window * get_this(void * h)
            //{
            //    return ak::cast<window*>(GetWindowLongPtr((HWND)h, GWL_USERDATA));
            //}

            static std::map<void*, window*> _map;

            static void set_this(void * h, window * w)
            {
                _map[h] = w;
            }

            static window * get_this(void * h)
            {
                if (_map.find(h) == _map.end())
                    return 0;
                return _map[h];
            }

            LRESULT CALLBACK procedure(HWND h, UINT m, WPARAM w, LPARAM l)
            {
                //window * This = get_this(h);
                //if (This != 0 && This->message(m, w, l))
                    return 0;

                //if (m == WM_PAINT)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_paint(*this_, 0);
                //    return 0;
                //}
                //else if (m == WM_MOUSEMOVE)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_mousemove(*this_, point<int>(LOWORD(l), HIWORD(l)));
                //    return 0;
                //}
                //else if (m == WM_MOUSELEAVE)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_mouseleave(*this_, 0);
                //    return 0;
                //}
                //else if (m == WM_LBUTTONDOWN)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_buttondown(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 1));
                //    return 0;
                //}
                //else if (m == WM_LBUTTONUP)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_buttonup(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 1));
                //    return 0;
                //}
                //else if (m == WM_RBUTTONDOWN)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_buttondown(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 2));
                //    return 0;
                //}
                //else if (m == WM_RBUTTONUP)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_buttonup(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 2));
                //    return 0;
                //}
                //else if (m == WM_MBUTTONDOWN)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_buttondown(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 3));
                //    return 0;
                //}
                //else if (m == WM_MBUTTONUP)
                //{
                //    window * this_ = get_this(h);
                //    this_->wm_buttonup(*this_, structure<point<int>, int>(point<int>(LOWORD(l), HIWORD(l)), 3));
                //    return 0;
                //}
                //else if (m == WM_CLOSE)
                //{
                //    window::quit();
                //    return 0;
                //}

                return ::DefWindowProc(h, m, w, l);
            }
        }

        window::window() : _inernal_handle(0)
        { }

        window::~window()
        {
            //_internal::set_this(get_inernal_handle(), 0);
        }

        void window::create(const std::string & cls, const std::string & title, int class_style, int window_style, int window_style_ex, ak::size<unsigned int> window_size, const window & parent)
        {            
            WNDCLASSEXA wcx;
            if (!GetClassInfoExA(GetModuleHandle(0), cls.c_str(), &wcx))
            {
                wcx.cbSize = sizeof(wcx);
                wcx.style = class_style;//CS_HREDRAW | CS_VREDRAW;
                wcx.lpfnWndProc = _internal::procedure;
                wcx.cbClsExtra = 0;
                wcx.cbWndExtra = 0;
                wcx.hInstance = GetModuleHandle(0);
                wcx.hIcon = NULL;
                wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
                wcx.hbrBackground = (HBRUSH)NULL_BRUSH;//NULL;
                wcx.lpszMenuName = NULL;
                wcx.lpszClassName = cls.c_str();
                wcx.hIconSm = NULL; 
                if (!RegisterClassExA(&wcx))
                    throw ak::exception() << "window::create() : RegisterClassExA = 0";
            }

            unsigned int stex = window_style_ex;//WS_EX_LAYERED;
            unsigned int st = window_style;//WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
            unsigned int x = CW_USEDEFAULT;
            unsigned int y = CW_USEDEFAULT;


            void * w = CreateWindowExA(stex, cls.c_str(), title.c_str(), st, 
                x, y, window_size.width, window_size.height,
                (HWND)parent.get_inernal_handle(), NULL, GetModuleHandle(0), 0);

            _inernal_handle = w;
            std::string err = ak::system::get_last_error(false);
            if (!is_valid_handle())
                throw ak::exception() << "windows::create() : CreateWindowExA = " << w ;
            _internal::set_this(w, this);
            void * proc = (void*)::GetWindowLongA((HWND)get_inernal_handle(), GWL_WNDPROC);
            if (proc != _internal::procedure)
            {
                ::SetWindowLongA((HWND)get_inernal_handle(), GWL_WNDPROC, (LONG)_internal::procedure);
            }
        }

        void window::create(const std::string & cls, const std::string & title, int class_style, int window_style, int window_style_ex, const ak::rectangle<int> & window_size, const window & parent)
        {            
            WNDCLASSEXA wcx;
            if (!GetClassInfoExA(GetModuleHandle(0), cls.c_str(), &wcx))
            {
                wcx.cbSize = sizeof(wcx);
                wcx.style = class_style;//CS_HREDRAW | CS_VREDRAW;
                wcx.lpfnWndProc = _internal::procedure;
                wcx.cbClsExtra = 0;
                wcx.cbWndExtra = 0;
                wcx.hInstance = GetModuleHandle(0);
                wcx.hIcon = NULL;
                wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
                wcx.hbrBackground = (HBRUSH)NULL_BRUSH;//NULL;
                wcx.lpszMenuName = NULL;
                wcx.lpszClassName = cls.c_str();
                wcx.hIconSm = NULL; 
                if (!RegisterClassExA(&wcx))
                    throw ak::exception() << "window::create() : RegisterClassExA = 0";
            }

            unsigned int stex = window_style_ex;//WS_EX_LAYERED;
            unsigned int st = window_style;//WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
            unsigned int x = CW_USEDEFAULT;
            unsigned int y = CW_USEDEFAULT;


            void * w = CreateWindowExA(stex, cls.c_str(), title.c_str(), st, 
                window_size.get_location().x, window_size.get_location().y, window_size.get_size().width, window_size.get_size().height,
                (HWND)parent.get_inernal_handle(), NULL, GetModuleHandle(0), 0);

            _inernal_handle = w;
            std::string err = ak::system::get_last_error(false);
            if (!is_valid_handle())
                throw ak::exception() << "windows::create() : CreateWindowExA = " << w ;
            _internal::set_this(w, this);
            void * proc = (void*)::GetWindowLongA((HWND)get_inernal_handle(), GWL_WNDPROC);
            if (proc != _internal::procedure)
            {
                ::SetWindowLongA((HWND)get_inernal_handle(), GWL_WNDPROC, (LONG)_internal::procedure);
            }
        }

        void window::create(const std::wstring & cls, const std::wstring & title, int class_style, int window_style, int window_style_ex, ak::size<unsigned int> window_size)
        {            
            WNDCLASSEXW wcx;
            if (!GetClassInfoExW(GetModuleHandle(0), cls.c_str(), &wcx))
            {
                wcx.cbSize = sizeof(wcx);
                wcx.style = class_style;//CS_HREDRAW | CS_VREDRAW;
                wcx.lpfnWndProc = _internal::procedure;
                wcx.cbClsExtra = 0;
                wcx.cbWndExtra = 0;
                wcx.hInstance = GetModuleHandle(0);
                wcx.hIcon = NULL;
                wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
                wcx.hbrBackground = (HBRUSH)NULL_BRUSH;//NULL;
                wcx.lpszMenuName = NULL;
                wcx.lpszClassName = cls.c_str();
                wcx.hIconSm = NULL; 
                if (!RegisterClassExW(&wcx))
                    throw ak::exception() << "window::create() : RegisterClassExA = 0";
            }

            unsigned int stex = window_style_ex;//WS_EX_LAYERED;
            unsigned int st = window_style;//WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
            unsigned int x = CW_USEDEFAULT;
            unsigned int y = CW_USEDEFAULT;


            void * w = CreateWindowExW(stex, cls.c_str(), title.c_str(), st, 
                x, y, window_size.width, window_size.height,
                NULL, NULL, GetModuleHandle(0), 0);

            _inernal_handle = w;
            if (!is_valid_handle())
                throw ak::exception() << "windows::create() : CreateWindowExA = " << w ;
            _internal::set_this(w, this);
            void * proc = (void*)::GetWindowLongA((HWND)get_inernal_handle(), GWL_WNDPROC);
            if (proc != _internal::procedure)
            {
                ::SetWindowLongW((HWND)get_inernal_handle(), GWL_WNDPROC, (LONG)_internal::procedure);
            }
        }

        void window::create(const std::wstring & cls, const std::wstring & text)
        {            
            WNDCLASSEXW wcx;
            if (!GetClassInfoExW(GetModuleHandle(0), cls.c_str(), &wcx))
            {
                wcx.cbSize = sizeof(wcx);
                wcx.style = CS_HREDRAW | CS_VREDRAW;
                wcx.lpfnWndProc = _internal::procedure;
                wcx.cbClsExtra = 0;
                wcx.cbWndExtra = 0;
                wcx.hInstance = GetModuleHandle(0);
                wcx.hIcon = NULL;
                wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
                wcx.hbrBackground = NULL;
                wcx.lpszMenuName = NULL;
                wcx.lpszClassName = cls.c_str();
                wcx.hIconSm = NULL; 
                if (!RegisterClassExW(&wcx))
                    throw ak::exception() << "window::create() : RegisterClassExW = 0";
            }

            unsigned int stex = 0;
            unsigned int st = WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
            unsigned int x = CW_USEDEFAULT;
            unsigned int y = CW_USEDEFAULT;
            unsigned int width = 800;
            unsigned int height = 600;

            void * w = CreateWindowExW(stex, cls.c_str(), text.c_str(),
                st, 
                x, y, width, height,
                NULL, NULL, GetModuleHandle(0), 0);

            _inernal_handle = w;
            if (!is_valid_handle())
                throw ak::exception() << "windows::create() : CreateWindowExA = " << w ;
            _internal::set_this(get_inernal_handle(), this);
        }

        bool window::is_valid_handle()
        {
            return get_inernal_handle() != 0 && get_inernal_handle() != (void *)-1;
        }

        bool window::message(unsigned int m, unsigned int wp, unsigned int lp)
        {
            bool retval = false;
            return retval;
        }

        int window::show_dialog()
        {
            ::ShowWindow((HWND)get_inernal_handle(), SW_SHOW);
            MSG msg;
            while (::GetMessageA(&msg,0,0,0))
            {
                ::TranslateMessage(&msg); 
                ::DispatchMessage(&msg); 
            }
            return (int)msg.wParam;
        }

        void window::show()
        {
            ::ShowWindow((HWND)get_inernal_handle(), SW_SHOW);
            UpdateWindow((HWND)get_inernal_handle());
        }

        void window::hide()
        {
            ::ShowWindow((HWND)get_inernal_handle(), SW_HIDE);
        }

        void window::invalidate()
        {
            ::InvalidateRect((HWND)get_inernal_handle(), NULL, FALSE);
        }

        void window::quit()
        {
            ::PostQuitMessage(0);
        }

        void window::update_layered(ak::ui::dc & dc)
        {
            RECT rt;
            ::GetWindowRect((HWND)get_inernal_handle(), &rt);
            SIZE sz = {rt.right - rt.left, rt.bottom - rt.top};
            POINT pt = {0, 0};
            BLENDFUNCTION blender = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
            ::UpdateLayeredWindow((HWND)get_inernal_handle(), GetDC(0), 0, &sz, (HDC)dc.get_internal_handle(), &pt, 0, &blender, ULW_ALPHA);
        }

        ak::rectangle<int> window::rectangle()
        {
            RECT rt;
            ::GetWindowRect((HWND)get_inernal_handle(), &rt);
            return ak::rectangle<int>(rt.left, rt.top, rt.right, rt.bottom);
        }

        void window::position(const ak::point<int> & pt)
        {
            SetWindowPos((HWND)get_inernal_handle(), 0,
                pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER);

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

