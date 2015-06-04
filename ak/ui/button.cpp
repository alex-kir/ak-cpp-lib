#include <ak/ui/button.h>

namespace ak
{
	namespace ui
	{
        button & button::create(const window & parent, int id, const std::string & text, const ak::rectangle<int> & rect)
        {
            window::create<char, int>("Button", text.c_str(), WS_CHILD | WS_CLIPSIBLINGS, 0, rect, parent);
            HFONT hFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
            ::SendMessageA((HWND)get_internal_handle(), WM_SETFONT, (WPARAM)hFont, 0);
            set_id(id);
            show();
            return *this;
        }

        button & button::create_2(const window & parent, int id, const std::string & text, const ak::rectangle<int> & rect)
        {
            window::create<char, int>("Button", text.c_str(), WS_CHILD | WS_CLIPSIBLINGS | BS_MULTILINE, 0, rect, parent);
            HFONT hFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
            ::SendMessageA((HWND)get_internal_handle(), WM_SETFONT, (WPARAM)hFont, 0);
            set_id(id);
            show();
            return *this;
        }

        button & button::create_checkbox(const window & parent, int id, const std::string & text, const ak::rectangle<int> & rect)
        {
            window::create<char, int>("Button", text.c_str(), WS_CHILD | WS_CLIPSIBLINGS | BS_AUTOCHECKBOX, 0, rect, parent);
            HFONT hFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
            ::SendMessageA((HWND)get_internal_handle(), WM_SETFONT, (WPARAM)hFont, 0);
            set_id(id);
            show();
            return *this;
        }

        bool button::get_check()
        {
            return ::SendMessageA((HWND)get_internal_handle(), BM_GETCHECK, 0, 0) == BST_CHECKED;
        }

        void button::set_check(bool c)
        {
            ::SendMessageA((HWND)get_internal_handle(), BM_SETCHECK, (WPARAM)(c ? BST_CHECKED : BST_UNCHECKED), 0);
        }
	}
}
        
