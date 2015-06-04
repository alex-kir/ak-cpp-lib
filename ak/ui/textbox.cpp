#include <ak/ui/textbox.h>

namespace ak
{
    namespace ui
    {
        textbox & textbox::create(const window & parent, const std::string & text, int x, int y, int width, int height)
        {
            window::create<char, int>(WC_EDITA, text, WS_CHILD | ES_AUTOHSCROLL /*ES_MULTILINE*/ , WS_EX_CLIENTEDGE, x, y, width, height, parent);
            show();
            return *this;
        }
    }
}

