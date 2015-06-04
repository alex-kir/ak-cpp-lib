#include <ak/ui/combobox.h>

namespace ak
{
    namespace ui
    {
        combobox & combobox::create(const window & parent, int id, const ak::point<int> & pt, const ak::size<int> & sz, const std::vector<std::string> & items)
        {
            window::create<char, int>("ComboBox", "", WS_CLIPSIBLINGS | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 0, pt, sz, parent);
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            ::SendMessageA((HWND)get_internal_handle(), WM_SETFONT, (WPARAM)hFont, 0);
            set_id(id);
            show();
            for (size_t i = 0; i < items.size(); i++)
                add_item(items[i]);
            return *this;
        }

        void combobox::add_item(const std::string & item)
        {
            ::SendMessageA((HWND)get_internal_handle(), CB_ADDSTRING, 0, (LPARAM)item.c_str()); 
        }

        void combobox::select(const std::string & item)
        {
            ::SendMessageA((HWND)get_internal_handle(), CB_SELECTSTRING, -1, (LPARAM)item.c_str()); 
        }
    }
}

