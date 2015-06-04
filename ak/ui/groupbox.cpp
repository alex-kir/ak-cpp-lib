#include <ak/ui/groupbox.h>

namespace ak
{
    namespace ui
    {
        groupbox & groupbox::create(const window & parent, const std::string & text, int x1, int y1, int x2, int y2)
        {
            window::create<char, int>(WC_BUTTONA, text, WS_CLIPSIBLINGS | WS_CHILD | BS_GROUPBOX, 0, rectanglei(x1, y1, x2, y2), parent);
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            ::SendMessageA((HWND)get_internal_handle(), WM_SETFONT, (WPARAM)hFont, 0);
            show();
            return *this;
        }
    }
}

