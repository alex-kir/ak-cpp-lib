#include <ak/ui/window.h>
#include <ak/cast.h>
#include <ak/ui/dc.h>

namespace ak
{
    namespace ui
    {
        window::window()
        { }

        window::~window()
        {
        }

        void window::create(const std::string & cls, int class_style, const std::string & title, int window_style, int window_style_ex, int x, int y, int width, int height, const window & parent)
        {
            WNDCLASSEXA wcx;
            if (!GetClassInfoExA(GetModuleHandle(0), cls.c_str(), &wcx))
            {
                //wcx.cbSize = sizeof(wcx);
                //wcx.style = class_style;//CS_HREDRAW | CS_VREDRAW;
                //wcx.lpfnWndProc = _internal::procedure;
                //wcx.cbClsExtra = 0;
                //wcx.cbWndExtra = 0;
                //wcx.hInstance = GetModuleHandle(0);
                //wcx.hIcon = NULL;
                //wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
                //wcx.hbrBackground = (HBRUSH)NULL_BRUSH;//NULL;
                //wcx.lpszMenuName = NULL;
                //wcx.lpszClassName = cls.c_str();
                //wcx.hIconSm = NULL; 
                //if (!RegisterClassExA(&wcx))
                    throw ak::exception() << "GetClassInfoExA()";
            }

            object<HWND>(::CreateWindowExA(window_style_ex, cls.c_str(), title.c_str(), window_style, x, y, width, height, (HWND)parent.get_internal_handle(), NULL, ::GetModuleHandle(0), 0));
            if (!is_valid_handle())
                throw ak::exception() << "windows::create() : CreateWindowExA() " << ak::system::get_last_error(false);
        }

        void window::create(const std::wstring & cls, int class_style, const std::wstring & title, int window_style, int window_style_ex, int x, int y, int width, int height, const window & parent)
        {
            WNDCLASSEXW wcx;
            if (!GetClassInfoExW(GetModuleHandle(0), cls.c_str(), &wcx))
            {
                //wcx.cbSize = sizeof(wcx);
                //wcx.style = class_style;//CS_HREDRAW | CS_VREDRAW;
                //wcx.lpfnWndProc = _internal::procedure;
                //wcx.cbClsExtra = 0;
                //wcx.cbWndExtra = 0;
                //wcx.hInstance = GetModuleHandle(0);
                //wcx.hIcon = NULL;
                //wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
                //wcx.hbrBackground = (HBRUSH)NULL_BRUSH;//NULL;
                //wcx.lpszMenuName = NULL;
                //wcx.lpszClassName = cls.c_str();
                //wcx.hIconSm = NULL; 
                //if (!RegisterClassExA(&wcx))
                    throw ak::exception() << "GetClassInfoExA()";
            }

            object<HWND>(::CreateWindowExW(window_style_ex, cls.c_str(), title.c_str(), window_style, x, y, width, height, (HWND)parent.get_internal_handle(), NULL, ::GetModuleHandle(0), 0));
            if (!is_valid_handle())
                throw ak::exception() << "windows::create() : CreateWindowExA() " << ak::system::get_last_error(false);
        }



        void window::destroy()
        {
            ::DestroyWindow((HWND)get_internal_handle());
            object(0);
        }

        int window::get_id()
        {
            return ::GetWindowLongW((HWND)get_internal_handle(), GWL_ID);
        }

        void window::set_id(int id)
        {
            ::SetWindowLongW((HWND)get_internal_handle(), GWL_ID, id);
        }

        void window::set_capture()
        {
            ::SetCapture(object<HWND>());
        }

        void window::release_capture()
        {
            ::ReleaseCapture();
        }

        void window::show()
        {
            ::ShowWindow((HWND)get_internal_handle(), SW_SHOW);
            ::UpdateWindow((HWND)get_internal_handle());
            ::SetForegroundWindow((HWND)get_internal_handle());
        }

        void window::show_no_activate()
        {
            ::ShowWindow((HWND)get_internal_handle(), SW_SHOWNOACTIVATE);
        }

        void window::hide()
        {
            ::ShowWindow((HWND)get_internal_handle(), SW_HIDE);
        }

        bool window::is_show()
        {
            return TRUE == IsWindowVisible((HWND)get_internal_handle());
        }

        void window::invalidate()
        {
            ::InvalidateRect((HWND)get_internal_handle(), NULL, FALSE);
        }

        int window::post_message(int m, int wparam, int lparam)
        {
            return ::PostMessageA(*this, m, wparam, lparam);
        }

        void window::quit()
        {
            ::PostQuitMessage(0);
        }

        void window::update_layered(ak::ui::dc & dc)
        {
            RECT rt;
            ::GetWindowRect((HWND)get_internal_handle(), &rt);
            SIZE sz = {rt.right - rt.left, rt.bottom - rt.top};
            POINT pt = {0, 0};
            BLENDFUNCTION blender = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
            ::UpdateLayeredWindow((HWND)get_internal_handle(), GetDC(0), 0, &sz, dc.object(), &pt, 0, &blender, ULW_ALPHA);
        }

        window window::parent()
        {
            window w;
            w.object<HWND>(::GetParent((HWND)get_internal_handle()));
            return w;
        }

        ak::rectanglei window::clientrectangle()
        {
            WINDOWINFO wi;
            wi.cbSize = sizeof(wi);
            ::GetWindowInfo((HWND)get_internal_handle(), &wi);
            return ak::rectanglei(wi.rcClient.left, wi.rcClient.top, wi.rcClient.right, wi.rcClient.bottom);
        }

        ak::rectangle<int> window::rectangle(bool onscreen)
        {
            if (onscreen)
            {
                RECT rt;
                ::GetWindowRect((HWND)get_internal_handle(), &rt);
                return ak::rectanglei(rt.left, rt.top, rt.right, rt.bottom);
            }
            else
            {
                rectanglei rt1 = clientrectangle();
                rectanglei rt2 = parent().clientrectangle();
                return ak::rectanglei(rt1.location() - rt2.location(), rt1.size());
            }
        }

        void window::position(int x, int y)
        {
            ::SetWindowPos((HWND)get_internal_handle(), 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER);
        }

        void window::size(int width, int height)
        {
            ::SetWindowPos((HWND)get_internal_handle(), 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER);
        }

        void window::rectangle(int x, int y, int width, int height)
        {
            ::SetWindowPos(object<HWND>(), 0, x, y, width, height, SWP_NOOWNERZORDER);
        }

        void window::clientsize(int width, int height)
        {
            RECT rt;
            ::SetRect(&rt, 0, 0, width, height);
            WINDOWINFO wi;
            wi.cbSize = sizeof(wi);
            ::GetWindowInfo((HWND)get_internal_handle(), &wi);
            ::AdjustWindowRectEx(&rt, wi.dwStyle, false, wi.dwExStyle);
            size(rt.right - rt.left, rt.bottom - rt.top);
        }

        void window::adjust_size(int cx, int cy)
        {
            WINDOWPLACEMENT wp;
            wp.length = sizeof(wp);
            int right1 = 0;
            int bottom1 = 0;

            HWND wnd = ::GetWindow((HWND)get_internal_handle(), GW_CHILD);
            while (wnd)
            {
                ::GetWindowPlacement(wnd, &wp);
                right1 = std::max<int>(right1, wp.rcNormalPosition.right);
                bottom1 = std::max<int>(bottom1, wp.rcNormalPosition.bottom);
                wnd = ::GetWindow(wnd, GW_HWNDNEXT);
            }

            clientsize(right1 + cx, bottom1 + cy);
        }

        void window::adjust_height(int cy)
        {
            WINDOWPLACEMENT wp;
            wp.length = sizeof(wp);
            int bottom1 = 0;

            HWND wnd = ::GetWindow((HWND)get_internal_handle(), GW_CHILD);
            while (wnd)
            {
                ::GetWindowPlacement(wnd, &wp);
                bottom1 = std::max<int>(bottom1, wp.rcNormalPosition.bottom);
                wnd = ::GetWindow(wnd, GW_HWNDNEXT);
            }
            sizei sz = size(false);
            clientsize(sz.width, bottom1 + cy);
        }

        std::string window::get_text()
        {
            int sz = (int)::SendMessageA((HWND)get_internal_handle(), (UINT) WM_GETTEXTLENGTH, 0, 0);
            std::string text;
            text.resize(sz + 1);
            ::SendMessageA((HWND)get_internal_handle(), (UINT)WM_GETTEXT, sz + 1, (LPARAM)text.c_str());
            text.resize(sz);
            return text;
        }

        void window::set_text(const std::string & text)
        {
            ::SendMessageA((HWND)get_internal_handle(), (UINT)WM_SETTEXT, 0, (LPARAM)text.c_str());
        }

		std::string window::wnd_class_name()
		{
			char sz[300];
			int len = ::GetClassNameA((HWND)get_internal_handle(), sz, 299);
			return std::string(sz, len);
		}

        void window::set_timer(int id, int elapse)
        {
            ::SetTimer((HWND)get_internal_handle(), id, elapse, NULL);
        }
        
        void window::kill_timer(int id)
        {
            ::KillTimer((HWND)get_internal_handle(), id);
        }

        window & window::set_font()
        {
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            ::SendMessageA((HWND)get_internal_handle(), WM_SETFONT, (WPARAM)hFont, 0);
            return *this;
        }

		BOOL CALLBACK window_children_enum_proc(HWND h, std::vector<window> * pww)
		{
			pww->push_back(window(h));
			return true;
		}

		std::vector<window> window::children()
		{
			std::vector<window> ww;
			::EnumChildWindows((HWND)get_internal_handle(), (WNDENUMPROC)window_children_enum_proc, (LPARAM)&ww);
			return ww;
		}
    }
}
