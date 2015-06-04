#include <ak/ui/menu.h>
#include <ak/ui/window_utils.h>
namespace ak
{
    namespace ui
    {
        void menu::create()
        {
            object<HMENU>(::CreatePopupMenu());
        }

        void menu::destroy()
        {
            ::DestroyMenu(object<HMENU>());
            wnd.destroy();
        }

        int menu::show(const ak::point<int> & pt)
        {
            wnd.create();
            int retval = ::TrackPopupMenuEx(object<HMENU>(), TPM_NONOTIFY | TPM_RETURNCMD | TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, (HWND)wnd.get_internal_handle(), 0);
            wnd.destroy();
            return retval;
        }

        void menu::hide()
        {
            ::EndMenu();
        }

        void menu::append()
        {
            MENUITEMINFOA mii;
            mii.cbSize = sizeof(MENUITEMINFO);
            mii.fMask = MIIM_TYPE;
            mii.fType = MFT_SEPARATOR;
            mii.dwTypeData = "-";
            ::InsertMenuItemA(object<HMENU>(), 0x79999999, TRUE, &mii);
        }

        void menu::append(const std::string & text, int id)
        {
            MENUITEMINFOA mii;
            mii.cbSize = sizeof(MENUITEMINFO);
            mii.fMask = MIIM_STRING | MIIM_ID;
            mii.fType = MFT_STRING;
            mii.dwTypeData = (LPSTR)text.c_str();
            mii.wID = id;
            ::InsertMenuItemA(object<HMENU>(), 0x79999999, TRUE, &mii);
        }

        void menu::append(menu & sub)
        {
            ::AppendMenuA(object<HMENU>(), MF_POPUP, (UINT_PTR)&sub, MF_STRING);
        }

        menu menu::submenu(int i)
        {
            menu m;
            m.object<HMENU>(::GetSubMenu(object<HMENU>(), 0));
            return m;
        }
    }
}