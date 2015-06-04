#include <ak/ui/label.h>

namespace ak
{
    namespace ui
    {
        label & label::create(const window & parent, const std::string & text, const ak::rectangle<int> & rect)
        {
            window::create<char, int>("Static", text.c_str(), WS_CHILD | WS_CLIPSIBLINGS, 0, rect, parent);
            HFONT hFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
            ::SendMessageA((HWND)get_internal_handle(), WM_SETFONT, (WPARAM)hFont, 0);
            show();
            return *this;
        }

        label & label::create_icon(const window & parent, const ak::rectangle<int> & rect)
        {
            window::create<char, int>("Static", "", SS_ICON | WS_CHILD | SS_CENTERIMAGE, 0, rect, parent);
            HFONT hFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
            ::SendMessageA((HWND)get_internal_handle(), WM_SETFONT, (WPARAM)hFont, 0);
            show();
            ::SendMessageA((HWND)get_internal_handle(), STM_SETICON, (WPARAM)LoadIcon(NULL, IDI_ASTERISK), 0);
            return *this;
        }
    }
}

