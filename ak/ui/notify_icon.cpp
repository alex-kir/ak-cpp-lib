#pragma once
#include <ak/ui/notify_icon.h>
#include <ak/system/user_io.h>
#include <algorithm>

namespace ak
{
    namespace ui
    {
        namespace _notify_icon_internal
        {
            int message_id = 0xf00d;

            LRESULT CALLBACK procedure(HWND h, UINT m, WPARAM w, LPARAM l)
            {
                notify_icon * _this = (notify_icon*)w;
                //notify_icon * tthis = (notify_icon*)::GetWindowLongA(h, GWL_ID);
                if (m == message_id && _this)
                {
                    int n_event = LOWORD(l);

                    if (false) { }
                    else if (n_event == WM_LBUTTONDOWN)
                    {
                        _this->on_mouse_left_down.notify(ak::notification_args().add("Location", ak::system::user_io::cursor_position()));
                    }
                    else if (n_event == WM_LBUTTONUP)
                    {
                        _this->on_mouse_left_up.notify(ak::notification_args().add("Location", ak::system::user_io::cursor_position()));
                    }
                    else if (n_event == WM_LBUTTONDBLCLK)
                    {
                        _this->on_mouse_left_dblclk.notify(ak::notification_args().add("Location", ak::system::user_io::cursor_position()));
                    }
                    else if (n_event == WM_RBUTTONDOWN)
                    {
                        _this->on_mouse_right_down.notify(ak::notification_args().add("Location", ak::system::user_io::cursor_position()));
                    }
                    else if (n_event == WM_RBUTTONUP)
                    {
                        _this->on_mouse_right_up.notify(ak::notification_args().add("Location", ak::system::user_io::cursor_position()));
                    }
                    else if (n_event == WM_RBUTTONDBLCLK)
                    {
                        _this->on_mouse_right_dblclk.notify(ak::notification_args().add("Location", ak::system::user_io::cursor_position()));
                    }
                    else if (n_event == WM_CONTEXTMENU)
                    {
                        _this->on_contextmenu.notify(ak::notification_args().add("Location", ak::system::user_io::cursor_position()));
                    }
                    return true;
                }
                return false;
            }
        }

        notify_icon::notify_icon()
        {
            _message_wnd.create<char, int>("Message", "", 0, 0, ak::size<unsigned int>(0,0));
            ::SetWindowLongA(_message_wnd.object<HWND>(), GWL_WNDPROC, ak::cast_ri<LONG>(_notify_icon_internal::procedure));
        }

        notify_icon::~notify_icon()
        {
            hide();
        }

        notify_icon & notify_icon::set_tip(const std::string & tip)
        {
            _tip = tip;
            return *this;
        }

        notify_icon & notify_icon::set_icon(const icon & ico)
        {
            _ico = ico;
            return *this;
        }

        bool notify_icon::show()
        {
            NOTIFYICONDATAA data;
            data.cbSize = sizeof(data);
            data.hWnd = (HWND)_message_wnd.get_internal_handle();
            data.uID = ak::cast_ri<UINT>(this);
            data.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
            if (_ico.empty())
            {
                data.hIcon = ui::icon::system_icon_asterisk().handle<HICON>();
            }
            else
            {
                data.hIcon = _ico.handle<HICON>();
            }
            data.uCallbackMessage = _notify_icon_internal::message_id;
            std::fill_n(data.szTip, 64, 0);
            std::copy(_tip.begin(), _tip.begin() + std::min<int>((int)_tip.size(), 63), data.szTip);
            return TRUE == ::Shell_NotifyIconA(NIM_ADD, &data);
        }

        void notify_icon::hide()
        {
            NOTIFYICONDATAA data;
            data.cbSize = sizeof(data);
            data.hWnd = (HWND)_message_wnd.get_internal_handle();
            data.uID = ak::cast_ri<UINT>(this);
            Shell_NotifyIconA(NIM_DELETE, &data);
        }

        void notify_icon::refresh()
        {
            NOTIFYICONDATAA data;
            data.cbSize = sizeof(data);
            data.hWnd = (HWND)_message_wnd.get_internal_handle();
            data.uID = ak::cast_ri<UINT>(this);
            data.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
            if (_ico.empty())
            {
                data.hIcon = ui::icon::system_icon_asterisk().handle<HICON>();
            }
            else
            {
                data.hIcon = _ico.handle<HICON>();
            }
            data.uCallbackMessage = _notify_icon_internal::message_id;
            std::fill_n(data.szTip, 64, 0);
            std::copy(_tip.begin(), _tip.begin() + std::min<int>((int)_tip.size(), 63), data.szTip);
            ::Shell_NotifyIconA(NIM_MODIFY, &data);
        }
    }
}
