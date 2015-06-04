#include <ak/ui/icon.h>

namespace ak
{
    namespace ui
    {
        void icon::release()
        {
            ::DestroyIcon(handle<HICON>());
            handle((void*)0);
        }

        void icon::load_from_file(const std::string & filename)
        {
            handle(::LoadImageA(0, filename.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE));
        }

        void icon::load_from_resource(int res_id)
        {
            handle(::LoadIconA(::GetModuleHandle(NULL), MAKEINTRESOURCEA(res_id)));
        }

        icon icon::system_icon_asterisk()
        {
            icon ico;
            ico.handle(::LoadIcon(NULL, IDI_ASTERISK));
            return ico;
        }
    }
}